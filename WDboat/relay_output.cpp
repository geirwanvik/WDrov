#include "relay_output.h"

_RelayOutput RelayOutput[8];

void _RelayOutput::Init(byte _name, byte _pin)
{
	name = _name;
	pin = _pin;
	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
}

void _RelayOutput::SetOutput(byte _name, byte _value)
{
	if (name == _name)
	{
		digitalWrite(pin, _value);
	}
}
