#pragma once
#include "Arduino.h"
#if !(defined USE_MPU600)
class _MPU
{
public:
	void init(void);
	void readGyro(int16_t(&data)[3]);
	void readAcc(int16_t(&data)[3]);
	void readMag(int16_t(&data)[3]);
	void calibrateAcc(void);
	void beginCalibration(void);
	void endCalibration(void);
private:
	void initGyro(void);
	void initAcc(void);
	void initMag(void);
	bool calibrated;
	int16_t accOffset[3];
	uint8_t status;
	float magGain[3];
	int16_t magOffset[3];
};
extern _MPU MPU;
#endif
