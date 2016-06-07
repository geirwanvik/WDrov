#include "mpu6000.h"
#ifdef USE_MPU600
#include "hmc5843.h"
#include "spihelper.h"
enum AXIS { ROLL, PITCH, YAW };
_MPU MPU;

void _MPU::init()
{
	calibrated = false;
	SpiHelper.init();
	initGyro();
	initAcc();
	SpiHelper.setClockSpeed(ClockSpeeds::Clock_8Mhz);
	HMC.init();
}
void _MPU::readGyro(int16_t(&data)[3])
{
	static int16_t calibrating = 512;
	static int16_t previousData[3] = { 0, 0, 0 };
	static int16_t gyroZero[3] = { 0, 0, 0 };
	static int32_t g[3];
	uint8_t raw[6];
	uint8_t axis;

	SpiHelper.read(0x43, raw, 6);
	data[PITCH] = (int16_t)(raw[0] << 8 | raw[1]) >> 2;
	data[ROLL] = -(int16_t)(raw[2] << 8 | raw[3]) >> 2;
	data[YAW] = -(int16_t)(raw[4] << 8 | raw[5]) >> 2;
	
	if (calibrating>0)
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

		SpiHelper.read(0x3B, raw, 6);
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
			calibrated = true;
			accOffset[ROLL] = (a[ROLL] + 256) >> 9;
			accOffset[PITCH] = (a[PITCH] + 256) >> 9;
			accOffset[YAW] = ((a[YAW] + 256) >> 9) - (512);
			//SaveMemory();
		}
		calibrating--;
		delay(5);
	}
}
void _MPU::readAcc(int16_t(&data)[3])
{
	uint8_t raw[6];
	SpiHelper.read(0x3B, raw, 6);
	data[ROLL] = (int16_t)(raw[0] << 8 | raw[1]) >> 3;
	data[PITCH] = (int16_t)(raw[2] << 8 | raw[3]) >> 3;
	data[YAW] = (int16_t)(raw[4] << 8 | raw[5]) >> 3;

	if (calibrated)
	{
		data[ROLL] -= accOffset[ROLL];
		data[PITCH] -= accOffset[PITCH];
		data[YAW] -= accOffset[YAW];
	}
}

void _MPU::initGyro()
{
	//PWR_MGMT_1    -- DEVICE_RESET 1
	SpiHelper.write(0x6B, 0x80);
	delay(100);

	//SPI mode enabled
	SpiHelper.write(0x6A, 0x10);

	//PWR_MGMT_1    -- SLEEP 0; CYCLE 0; TEMP_DIS 0; CLKSEL 3 (PLL with Z Gyro reference)
	SpiHelper.write(0x6B, 0x03);
	delay(5);

	//CONFIG        -- DLPF_CFG = 3 => ACC bandwidth = 44Hz GYRO bandwidth = 42Hz)
	SpiHelper.write(0x1A, 0x03);
	delay(5);

	//GYRO_CONFIG   -- FS_SEL = 3: Full scale set to 2000 deg/sec
	SpiHelper.write(0x1B, 0x18);
	delay(5);

}
void _MPU::initAcc()
{
	//ACCEL_CONFIG  -- AFS_SEL=2 (Full Scale = +/-8G)  ; ACCELL_HPF=0
	SpiHelper.write(0x1C, 0x10);
}

void _MPU::readMag(int16_t(&data)[3])
{
	HMC.readMag(data);
}

void _MPU::beginCalibration(void)
{
	HMC.beginCalibration();
}
void _MPU::endCalibration(void)
{
	HMC.endCalibration();
}

#endif
