#pragma once
#include "Arduino.h"

class _RelayOutput
{
public:
	void Init(byte _name, byte _pin);
	void SetOutput(byte _name, byte _value);

private:
	byte name;
	byte pin;
};
extern _RelayOutput RelayOutput[8];
