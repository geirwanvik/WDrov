#include "button_led.h"

ButtonLed buttonLeds[8];

void ButtonLed::Init(byte _name, byte _buttonPin, byte _ledPin)
{
	name = _name;
	ledPin = _ledPin;
	buttonPin = _buttonPin;
	digitalWrite(ledPin, LOW);
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT);
	debounceDelay = 100;
	debounceTime = 0;
	lastValue = 0;
	value = 0;
	blink = 0;
	lastInput = 0;
	buttonState = 0;
}

void ButtonLed::ReadButton()
{
	byte input = digitalRead(buttonPin);
	if (input != lastInput)
	{
		debounceTime = millis();
	}
	if ((millis() - debounceTime) > debounceDelay)
	{
		if (input != buttonState)
		{
			buttonState = input;
			if (buttonState == HIGH)
			{
				value = !value;
			}
		}
	}
	lastInput = input;
}

void ButtonLed::SetLed(byte _name, byte _value)
{
	if (name == _name)
	{
		value = lastValue = _value;
		digitalWrite(ledPin, value);
	}
}

byte ButtonLed::GetValue()
{
	lastValue = value;
	return value;
}
byte ButtonLed::GetName()
{
	return name;
}
byte ButtonLed::ButtonChanged()
{
	if (lastValue != value)
		return true;
	return false;
}

void ButtonLed::Blink()
{
	if ((millis() - blinkTime) > 500)
	{
		if (blink)
		{
			blink = 0;
		}
		else
		{
			blink = 1;
		}
		blinkTime = millis();
		digitalWrite(ledPin, blink);
	}
}
