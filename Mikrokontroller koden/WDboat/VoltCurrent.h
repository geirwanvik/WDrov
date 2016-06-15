#pragma once
#include "Arduino.h"

class _VOLTCURRENT
{
public:
	void Init(void);
	void Update(void);
	float Current;
	float Voltage;

private:
	float prevRawVolt;
	float prevRawCurrent;
};

extern _VOLTCURRENT VoltCurrent;