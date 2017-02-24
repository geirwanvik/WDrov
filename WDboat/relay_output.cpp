#include "relay_output.h"
#include "CommandList.h"

_RelayOutput RelayOutput[8];

void _RelayOutput::Init(byte _name, byte _pin)
{
	name = _name;
	pin = _pin;
  lastValue = 0;
	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
}

void _RelayOutput::SetOutput(byte _name, byte _value)
{
	if (name == _name)
	{
    if ( _value != lastValue)
    {
		  digitalWrite(pin, _value);
      lastValue = _value;
    }
	}
}
