#include "button_led.h"

ButtonLed buttonLeds[8];

void ButtonLed::Init(byte _name, byte _buttonPin, byte _ledPin, byte _relayPin)
{
	name = _name;
	ledPin = _ledPin;
	buttonPin = _buttonPin;
	relayPin = _relayPin;
	digitalWrite(ledPin, LOW);
	pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT_PULLUP);
	digitalWrite(relayPin, LOW);
	pinMode(relayPin, OUTPUT);
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
			if (buttonState == LOW)
			{
				value = !value;
				digitalWrite(relayPin, value);
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
}

void ButtonLed::SetOutputs(byte _name, byte _value)
{
	if (name == _name)
	{
		value = lastValue = _value;
		digitalWrite(relayPin, value);
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
