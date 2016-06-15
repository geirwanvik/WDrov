#include "VoltCurrent.h"
#include "pins.h"

_VOLTCURRENT VoltCurrent;

void _VOLTCURRENT::Init(void)
{
	pinMode(CURRENT_SENSOR, INPUT);
	pinMode(VOLTAGE_SENSOR, INPUT);

	prevRawVolt = (float)analogRead(VOLTAGE_SENSOR);
	prevRawCurrent = (float)analogRead(CURRENT_SENSOR);
}

void _VOLTCURRENT::Update(void)
{
	const float alpha = 0.99;

	// Current calucaltion
	const float mVperAmp = 0.100;

	float filterValue = (prevRawCurrent * alpha) + ((float)analogRead(CURRENT_SENSOR) * (1 - alpha));
	prevRawCurrent = filterValue;

	float voltage = (float)(0.0049 * filterValue) - 2.5;
	Current = voltage / mVperAmp;

	// Voltage calculation
	const float R1 = 29970.0;
	const float R2 = 7480.0;

	filterValue = (prevRawVolt * alpha) + ((float)analogRead(VOLTAGE_SENSOR) * (1 - alpha));
	prevRawVolt = filterValue;
	voltage = (float)(0.0049 * filterValue);
	Voltage = voltage / (R2 / (R1 + R2));
}