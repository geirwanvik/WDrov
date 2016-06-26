#pragma once
#include "Arduino.h"
class ButtonLed
{
public:
	void Init(byte _name, byte _buttonPin, byte _ledPin, byte _relayPin);
	void ReadButton();
	void SetOutputs(byte _name, byte _value);
	byte GetValue();
	byte GetName();
	byte ButtonChanged();
	void Blink();

private:
	byte name;
	byte buttonPin;
	byte ledPin;
	byte relayPin;
	byte value;
	byte lastValue;
	byte blink;
	unsigned long debounceTime;
	byte debounceDelay;
	unsigned long blinkTime;
	byte lastInput;
	byte buttonState;
};

extern ButtonLed buttonLeds[8];

