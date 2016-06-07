#pragma once
#include "Arduino.h"
#include "pins.h"
#ifdef USE_MPU600
class _HMC
{
public:
	 void init(void);
	 void readMag(int16_t(&data)[3]);
	 void beginCalibration(void);
	 void endCalibration(void);
private:
	 uint8_t status;
	 float magGain[3];
	 int16_t magOffset[3];
};

extern _HMC HMC;
#endif