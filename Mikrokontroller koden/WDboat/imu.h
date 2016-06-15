#pragma once
#include "Arduino.h"

class _IMU
{
public:
	 void Init(void);
	 void Update(void);
	 float Roll;
	 float Pitch;
	 float Heading;
private:
	void getEstimatedAttitude(void);
	int16_t accSmooth[3]; // Filtered
	int16_t magData[3];
	int16_t accData[3];
	int16_t gyroData[3];
	int16_t prevGyro[3];
	int16_t gyroReadFirst[3];
	int16_t gyroReadLast[3];
};
extern _IMU IMU;
