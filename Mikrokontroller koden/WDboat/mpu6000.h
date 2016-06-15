#pragma once
#include "Arduino.h"
#include "pins.h"
#ifdef USE_MPU600
class _MPU
{
public:
	 void init(void);
	 void readGyro(int16_t(&data)[3]);
	 void readAcc(int16_t(&data)[3]);
	 void calibrateAcc(void);
	 void readMag(int16_t(&data)[3]);
	 void beginCalibration(void);
	 void endCalibration(void);
private:
	 void initGyro(void);
	 void initAcc(void);
	 bool calibrated;
	 int16_t accOffset[3];
};
extern _MPU MPU;
#endif