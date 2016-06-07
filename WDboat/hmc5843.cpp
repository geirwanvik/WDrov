#include "hmc5843.h"
#ifdef USE_MPU600
#include "i2cHelper.h"
#include "Streaming.h"

#define MAG_ADDRESS 0x1E
enum AXIS { ROLL, PITCH, YAW };
enum CALIB_STATUS { CONFIGURING, NORMAL, START, ONGOING, END };
_HMC HMC;


void _HMC::init()
{
	I2cHelper.init();
	delay(100);

	int16_t magADC[3];
	int32_t xyz_total[3] = { 0, 0, 0 };  // 32 bit totals so they won't overflow.
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
}

void _HMC::beginCalibration()
{
	status = START;
}
void _HMC::endCalibration()
{
	status = END;
}


void _HMC::readMag(int16_t(&data)[3])
{
	byte raw[6];
	static int16_t magZeroTempMin[3];
	static int16_t magZeroTempMax[3];
	uint8_t axis;

	I2cHelper.read(MAG_ADDRESS, 0x03, raw, 6);

	data[ROLL] = ((raw[0] << 8) | raw[1]);
	data[YAW] = -((raw[2] << 8) | raw[3]);
	data[PITCH] = ((raw[4] << 8) | raw[5]);

	if (status != CONFIGURING)
	{
		data[ROLL] = data[ROLL] * magGain[ROLL];
		data[PITCH] = data[PITCH] * magGain[PITCH];
		data[YAW] = data[YAW] * magGain[YAW];

		// we apply offset only once mag calibration is done
		data[ROLL] -= magOffset[ROLL];
		data[PITCH] -= magOffset[PITCH];
		data[YAW] -= magOffset[YAW];
	}

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
		//SaveMemory();
	}

}
#endif