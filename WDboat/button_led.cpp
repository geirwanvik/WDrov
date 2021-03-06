#include "button_led.h"

ButtonLed buttonLeds[8];

void ButtonLed::Init(byte _name, byte _buttonPin, byte _ledPin)
{
	name = _name;
	ledPin = _ledPin;
	buttonPin = _buttonPin;
	digitalWrite(ledPin, LOW);
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT_PULLUP);
	debounceDelay = 100;
	debounceTime = 0;
	lastValue = 0;
	value = 0;
	blink = 0;
	lastInput = 0;
	buttonState = 0;
	blinkSet = false;
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
			if (buttonState == LOW)
			{
				value = !value;
				if (value)
				{
					analogWrite(ledPin, 255);
				}
				else
				{
					analogWrite(ledPin, 0);
				}
			}
		}
	}
	lastInput = input;
	if (blinkSet)
	{
		blinkSet = false;
		if (value)
		{
			analogWrite(ledPin, 255);
		}
		else
		{
			analogWrite(ledPin, 0);
		}
	}
}

void ButtonLed::SetOutputs(byte _name, byte _value)
{
	if (name == _name)
	{
		value = lastValue = _value;
		if (value)
		{
			analogWrite(ledPin, 255);
		}
		else
		{
			analogWrite(ledPin, 0);
		}
	}
}
bool ButtonLed::CommandReceived(byte _name, byte _value)
{
	if (name == _name)
	{
		value = _value;
		if (value)
		{
			analogWrite(ledPin, 128);
		}
		else
		{
			analogWrite(ledPin, 0);
		}
		return true;
	}
	return false;
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
	blinkSet = true;
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
