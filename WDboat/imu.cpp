#include "imu.h"
#include "mpu6050.h"
#include "imuHelper.h"
_IMU IMU;

void _IMU::Init()
{
	int16_t temp[3];
	MPU.init();
	gyroReadLast[0] = gyroReadLast[1] = gyroReadLast[2] = 0;

	//Calibration
	for (int i = 0; i< 512; i++)
	{
		MPU.readGyro(temp);
		delay(5);
	}
}
uint32_t update = 0;
void _IMU::Update()
{
	static uint32_t lastTime = 0;

	//add 100ms delay
	if ((millis() - lastTime) >= 100)
	{
		MPU.readMag(magData);
		lastTime = millis();
	}

	MPU.readAcc(accData);
	getEstimatedAttitude();
 
	MPU.readGyro(gyroReadFirst);
	delayMicroseconds(650); //empirical, interleaving delay between 2 consecutive reads
	MPU.readGyro(gyroReadLast);

	for (byte axis = 0; axis < 3; axis++)
	{
		int16_t gyroADCinter = gyroReadLast[axis] + gyroReadFirst[axis];
		// empirical, we take a weighted value of the current and the previous values
		gyroData[axis] = (gyroADCinter + prevGyro[axis]) / 3;
		prevGyro[axis] = gyroADCinter >> 1;
	}
}

void _IMU::getEstimatedAttitude()
{
	static int32_t accLPF32[3] = { 0, 0, 1 };
	static float invG; // 1/|G|

	static t_fp_vector EstG;
	static t_int32_t_vector EstG32;
	static t_int32_t_vector EstM32;
	static t_fp_vector EstM;

	uint8_t axis;
	int32_t accMag = 0;
	float scale, deltaGyroAngle[3];
	uint8_t validAcc;
	static uint16_t previousT;
	uint16_t currentT = micros();

	scale = (currentT - previousT) * GYRO_SCALE; // GYRO_SCALE unit: radian/microsecond
	previousT = currentT;

	// Initialization
	for (axis = 0; axis < 3; axis++)
	{
		deltaGyroAngle[axis] = gyroData[axis] * scale; // radian

		accLPF32[axis] -= accLPF32[axis] >> ACC_LPF_FACTOR;
		accLPF32[axis] += accData[axis];
		accSmooth[axis] = accLPF32[axis] >> ACC_LPF_FACTOR;

		accMag += (int32_t)accSmooth[axis] * accSmooth[axis];
	}

	rotateV(&EstG.V, deltaGyroAngle);
	rotateV(&EstM.V, deltaGyroAngle);

	accMag = accMag * 100 / ((int32_t)ACC_1G*ACC_1G);
	validAcc = 72 < (uint16_t)accMag && (uint16_t)accMag < 133;
	// Apply complimentary filter (Gyro drift correction)
	// If accel magnitude >1.15G or <0.85G and ACC vector outside of the limit range => we neutralize the effect of accelerometers in the angle estimation.
	// To do that, we just skip filter, as EstV already rotated by Gyro
	for (axis = 0; axis < 3; axis++)
	{
		if (validAcc)
			EstG.A[axis] = (EstG.A[axis] * GYR_CMPF_FACTOR + accSmooth[axis]) * INV_GYR_CMPF_FACTOR;
		EstG32.A[axis] = EstG.A[axis]; //int32_t cross calculation is a little bit faster than float
		EstM.A[axis] = (EstM.A[axis] * GYR_CMPFM_FACTOR + magData[axis]) * INV_GYR_CMPFM_FACTOR;
		EstM32.A[axis] = EstM.A[axis];
	}

	// Attitude of the estimated vector
	int32_t sqGX_sqGZ = sq(EstG32.V.X) + sq(EstG32.V.Z);
	invG = InvSqrt(sqGX_sqGZ + sq(EstG32.V.Y));
	Pitch = (float)_atan2(EstG32.V.X, EstG32.V.Z)/10;
	Roll = (float)_atan2(EstG32.V.Y, InvSqrt(sqGX_sqGZ)*sqGX_sqGZ)/10;

	Heading = (float)_atan2(EstM32.V.Z * EstG32.V.X - EstM32.V.X * EstG32.V.Z,
		(EstM.V.Y * sqGX_sqGZ - (EstM32.V.X * EstG32.V.X + EstM32.V.Z * EstG32.V.Z) * EstG.V.Y)*invG)/10;
}
