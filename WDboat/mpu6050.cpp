#include "mpu6050.h"
#include "i2chelper.h"
#include <EEPROM.h>

#define MAG_ADDRESS 0x1E
#define MPU6050_ADDRESS 0x68
enum AXIS { ROLL, PITCH, YAW };
enum CALIB_STATUS { CONFIGURING, NORMAL, START, ONGOING, END };
enum EEPROM_SAVE_ADDRRESS { ACC_ADDR = 0x10, MAG_ADDR = 0x20};
struct EEPROM_SAVE_STRUCT { int16_t data[3]; };
_MPU MPU;

void _MPU::init()
{
	calibrated = false;
	I2cHelper.init();
	initGyro();
	initMag();
	initAcc();
}
void _MPU::readGyro(int16_t(&data)[3])
{
	static int16_t calibrating = 512;
	static int16_t previousData[3] = { 0, 0, 0 };
	static int16_t gyroZero[3] = { 0, 0, 0 };
	static int32_t g[3];
	uint8_t raw[6];
	uint8_t axis;

	I2cHelper.read(MPU6050_ADDRESS, 0x43, raw, 6);
	data[PITCH] = (int16_t)(raw[0] << 8 | raw[1]) >> 2;
	data[ROLL] = -(int16_t)(raw[2] << 8 | raw[3]) >> 2;
	data[YAW] = -(int16_t)(raw[4] << 8 | raw[5]) >> 2;

	if  (calibrating>0)
	{
		for (axis = 0; axis < 3; axis++)
		{
			// Reset g[axis] at start of calibration
			if (calibrating == 512)
			{
				g[axis] = 0;
			}
			// Sum up 512 readings
			g[axis] += data[axis];
			// Clear global variables for next reading
			data[axis] = 0;
			gyroZero[axis] = 0;
			if (calibrating == 1)
			{
				gyroZero[axis] = (g[axis] + 256) >> 9;
			}
		}
		calibrating--;
		delay(5);
	}

	for (axis = 0; axis < 3; axis++)
	{
		data[axis] -= gyroZero[axis];
		//anti gyro glitch, limit the variation between two consecutive readings
		data[axis] = constrain(data[axis], previousData[axis] - 800, previousData[axis] + 800);
		previousData[axis] = data[axis];
	}
}

void _MPU::calibrateAcc()
{
	int32_t a[3];
	int16_t calibrating = 512;

	while (calibrating>0)
	{
		uint8_t raw[6];
		int16_t data[3];

		I2cHelper.read(MPU6050_ADDRESS, 0x3B, raw, 6);
		data[ROLL] = (int16_t)(raw[0] << 8 | raw[1]) >> 3;
		data[PITCH] = (int16_t)(raw[2] << 8 | raw[3]) >> 3;
		data[YAW] = (int16_t)(raw[4] << 8 | raw[5]) >> 3;

		for (uint8_t axis = 0; axis < 3; axis++)
		{
			// Reset a[axis] at start of calibration
			if (calibrating == 512)
			{
				a[axis] = 0;
			}
			// Sum up 512 readings
			a[axis] += data[axis];
			// Clear global variables for next reading
			data[axis] = 0;
			accOffset[axis] = 0;
		}
		// Calculate average, shift Z down by ACC_1G ( 512 ) and store values
		if (calibrating == 1)
		{
			EEPROM_SAVE_STRUCT save;
			byte *ptr;
			calibrated = true;
			save.data[ROLL] = accOffset[ROLL] = (a[ROLL] + 256) >> 9;
			save.data[PITCH] = accOffset[PITCH] = (a[PITCH] + 256) >> 9;
			save.data[YAW] = accOffset[YAW] = ((a[YAW] + 256) >> 9) - (512);

			//Serial << "Acc offsets " << accOffset[0] << " " << accOffset[1] << " " << accOffset[2] << endl;

			ptr = (byte*)&save;
			for (byte i = 0; i < 6; i++)
			{
				EEPROM.write(ACC_ADDR + i, ptr[i]);
			}
		}
		calibrating--;
		delay(5);
	}
}
void _MPU::readAcc(int16_t(&data)[3])
{
	uint8_t raw[6];
	I2cHelper.read(MPU6050_ADDRESS, 0x3B, raw, 6);
	data[ROLL] = (int16_t)(raw[0] << 8 | raw[1]) >> 3;
	data[PITCH] = (int16_t)(raw[2] << 8 | raw[3]) >> 3;
	data[YAW] = (int16_t)(raw[4] << 8 | raw[5]) >> 3;

	data[ROLL] -= accOffset[ROLL];
	data[PITCH] -= accOffset[PITCH];
	data[YAW] -= accOffset[YAW];
}


void _MPU::beginCalibration()
{
	status = START;
}
void _MPU::endCalibration()
{
	status = END;
}


void _MPU::readMag(int16_t(&data)[3])
{
	byte raw[6];
	static int16_t magZeroTempMin[3];
	static int16_t magZeroTempMax[3];
	uint8_t axis;

	if (status == CONFIGURING)
	{
		I2cHelper.read(MAG_ADDRESS, 0x03, raw, 6);
	}
	else
	{
		I2cHelper.read(MPU6050_ADDRESS, 0x49, raw, 6);
	}

	data[ROLL] = ((raw[0] << 8) | raw[1]);
	data[YAW] = -((raw[2] << 8) | raw[3]);
	data[PITCH] = ((raw[4] << 8) | raw[5]);

	data[ROLL] = data[ROLL] * magGain[ROLL];
	data[PITCH] = data[PITCH] * magGain[PITCH];
	data[YAW] = data[YAW] * magGain[YAW];

	data[ROLL] -= magOffset[ROLL];
	data[PITCH] -= magOffset[PITCH];
	data[YAW] -= magOffset[YAW];

	if (status == START)
	{
		for (axis = 0; axis < 3; axis++)
		{
			magOffset[axis] = 0;
			magZeroTempMin[axis] = data[axis];
			magZeroTempMax[axis] = data[axis];
		}
		status = ONGOING;
	}

	if (status == ONGOING)
	{
		for (axis = 0; axis < 3; axis++)
		{
			if (data[axis] < magZeroTempMin[axis])
			{
				magZeroTempMin[axis] = data[axis];
			}
			if (data[axis] > magZeroTempMax[axis])
			{
				magZeroTempMax[axis] = data[axis];
			}
		}
	}
	if (status == END)
	{
		for (axis = 0; axis < 3; axis++)
		{
			magOffset[axis] = (magZeroTempMin[axis] + magZeroTempMax[axis]) >> 1;
		}
		status = NORMAL;

		EEPROM_SAVE_STRUCT save;
		byte *ptr;
		save.data[ROLL] = magOffset[ROLL];
		save.data[PITCH] = magOffset[PITCH];
		save.data[YAW] = magOffset[YAW];

		ptr = (byte*)&save;
		for (byte i = 0; i < 6; i++)
		{
			EEPROM.write(MAG_ADDR + i, ptr[i]);
		}
	}

}

void _MPU::initGyro()
{
	//PWR_MGMT_1    -- DEVICE_RESET 1
	I2cHelper.write(MPU6050_ADDRESS, 0x6B, 0x80);
	delay(100);

	//PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (PLL with Z Gyro reference)
	I2cHelper.write(MPU6050_ADDRESS, 0x6B, 0x03);
	delay(5);

	//CONFIG        -- DLPF_CFG = 3 => ACC bandwidth = 44Hz GYRO bandwidth = 42Hz)
	I2cHelper.write(MPU6050_ADDRESS, 0x1A, 0x03);
	delay(5);

	//GYRO_CONFIG   -- FS_SEL = 3: Full scale set to 2000 deg/sec
	I2cHelper.write(MPU6050_ADDRESS, 0x1B, 0x18);
	delay(5);

	// enable I2C bypass for AUX I2C
	//INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=1 ; CLKOUT_EN=0
	I2cHelper.write(MPU6050_ADDRESS, 0x37, 0x02);
}

void _MPU::initMag()
{
	int16_t magADC[3];
	int32_t xyz_total[3] = { 0, 0, 0 };  // 32 bit totals so they won't overflow.
	magGain[ROLL] = magGain[PITCH] = magGain[YAW] = 1.0;
	magOffset[ROLL] = magOffset[PITCH] = magOffset[YAW] = 0;
	status = CONFIGURING;
	bool bret = true;                // Error indicator

	delay(50);  //Wait before start
	I2cHelper.write(MAG_ADDRESS, 0x00, 0x010 + 0x01); // Reg A DOR=0x010 + MS1,MS0 set to pos bias

	// Note that the  very first measurement after a gain change maintains the same gain as the previous setting.
	// The new gain setting is effective from the second measurement and on.

	I2cHelper.write(MAG_ADDRESS, 0x01, 2 << 5);  //Set the Gain
	I2cHelper.write(MAG_ADDRESS, 0x02, 1);
	delay(100);
	readMag(magADC);  //Get one sample, and discard it

	for (uint8_t i = 0; i < 10; i++)
	{ //Collect 10 samples
		I2cHelper.write(MAG_ADDRESS, 0x02, 1);
		delay(100);
		readMag(magADC);   // Get the raw values in case the scales have already been changed.

		// Since the measurements are noisy, they should be averaged rather than taking the max.
		xyz_total[ROLL] += magADC[ROLL];
		xyz_total[PITCH] += magADC[PITCH];
		xyz_total[YAW] += magADC[YAW];

		// Detect saturation.
		if (-(1 << 12) >= min(magADC[ROLL], min(magADC[PITCH], magADC[YAW])))
		{
			bret = false;
			break;  // Breaks out of the for loop.  No sense in continuing if we saturated.
		}
	}

	// Apply the negative bias. (Same gain)
	I2cHelper.write(MAG_ADDRESS, 0x00, 0x010 + 0x02); // Reg A DOR=0x010 + MS1,MS0 set to negative bias.
	for (uint8_t i = 0; i < 10; i++)
	{
		I2cHelper.write(MAG_ADDRESS, 0x02, 1);
		delay(100);
		readMag(magADC);  // Get the raw values in case the scales have already been changed.

		// Since the measurements are noisy, they should be averaged.
		xyz_total[ROLL] -= magADC[ROLL];
		xyz_total[PITCH] -= magADC[PITCH];
		xyz_total[YAW] -= magADC[YAW];

		// Detect saturation.
		if (-(1 << 12) >= min(magADC[ROLL], min(magADC[PITCH], magADC[YAW])))
		{
			bret = false;
			break;  // Breaks out of the for loop.  No sense in continuing if we saturated.
		}
	}

	magGain[ROLL] = fabs(820.0*(+1.16)*2.0*10.0 / xyz_total[ROLL]);
	magGain[PITCH] = fabs(820.0*(+1.16)*2.0*10.0 / xyz_total[PITCH]);
	magGain[YAW] = fabs(820.0*(+1.08)*2.0*10.0 / xyz_total[YAW]);

	// leave test mode
	I2cHelper.write(MAG_ADDRESS, 0x00, 0x70); //Configuration Register A  -- 0 11 100 00  num samples: 8 ; output rate: 15Hz ; normal measurement mode
	I2cHelper.write(MAG_ADDRESS, 0x01, 0x20); //Configuration Register B  -- 001 00000    configuration gain 1.3Ga
	I2cHelper.write(MAG_ADDRESS, 0x02, 0x00); //Mode register             -- 000000 00    continuous Conversion Mode
	delay(100);

	if (!bret)
	{ //Something went wrong so get a best guess
		magGain[ROLL] = 1.0;
		magGain[PITCH] = 1.0;
		magGain[YAW] = 1.0;
	}

	status = NORMAL;

	EEPROM_SAVE_STRUCT save;
	byte *ptr;
	ptr = (byte*)&save;

	for (byte i = 0; i < 6; i++)
	{
		ptr[i] = EEPROM.read(MAG_ADDR + i);
	}
	magOffset[ROLL] = save.data[ROLL];
	magOffset[PITCH] = save.data[PITCH];
	magOffset[YAW] = save.data[YAW];

	//Serial << "Mag offsets " << magOffset[0] << " " << magOffset[1] << " " << magOffset[2] << endl;
}

void _MPU::initAcc()
{
	//ACCEL_CONFIG  -- AFS_SEL=2 (Full Scale = +/-8G)  ; ACCELL_HPF=0
	I2cHelper.write(MPU6050_ADDRESS, 0x1C, 0x10);

	//at this stage, the MAG is configured via the original MAG init function in I2C bypass mode
	//now we configure MPU as a I2C Master device to handle the MAG via the I2C AUX port (done here for HMC5883)

	//USER_CTRL     -- DMP_EN=0 ; FIFO_EN=0 ; I2C_MST_EN=1 (I2C master mode) ; I2C_IF_DIS=0 ; FIFO_RESET=0 ; I2C_MST_RESET=0 ; SIG_COND_RESET=0
	I2cHelper.write(MPU6050_ADDRESS, 0x6A, 0b00100000);

	//INT_PIN_CFG   -- INT_LEVEL=0 ; INT_OPEN=0 ; LATCH_INT_EN=0 ; INT_RD_CLEAR=0 ; FSYNC_INT_LEVEL=0 ; FSYNC_INT_EN=0 ; I2C_BYPASS_EN=0 ; CLKOUT_EN=0
	I2cHelper.write(MPU6050_ADDRESS, 0x37, 0x00);

	//I2C_MST_CTRL  -- MULT_MST_EN=0 ; WAIT_FOR_ES=0 ; SLV_3_FIFO_EN=0 ; I2C_MST_P_NSR=0 ; I2C_MST_CLK=13 (I2C slave speed bus = 400kHz)
	I2cHelper.write(MPU6050_ADDRESS, 0x24, 0x0D);

	//I2C_SLV0_ADDR -- I2C_SLV4_RW=1 (read operation) ; I2C_SLV4_ADDR=MAG_ADDRESS
	I2cHelper.write(MPU6050_ADDRESS, 0x25, 0x80 | MAG_ADDRESS);

	//I2C_SLV0_REG  -- 6 data bytes of MAG are stored in 6 registers. First register address is MAG_DATA_REGISTER
	I2cHelper.write(MPU6050_ADDRESS, 0x26, 0x03);

	//I2C_SLV0_CTRL -- I2C_SLV0_EN=1 ; I2C_SLV0_BYTE_SW=0 ; I2C_SLV0_REG_DIS=0 ; I2C_SLV0_GRP=0 ; I2C_SLV0_LEN=3 (3x2 bytes)
	I2cHelper.write(MPU6050_ADDRESS, 0x27, 0x86);

	EEPROM_SAVE_STRUCT save;
	byte *ptr;
	ptr = (byte*)&save;

	for (byte i = 0; i < 6; i++)
	{
		ptr[i] = EEPROM.read(ACC_ADDR + i);
	}
	accOffset[ROLL] = save.data[ROLL];
	accOffset[PITCH] = save.data[PITCH];
	accOffset[YAW] = save.data[YAW];
	//Serial << "Acc offsets " << accOffset[0] << " " << accOffset[1] << " " << accOffset[2] << endl;
}
