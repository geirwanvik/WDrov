#pragma once

#include "Arduino.h"

class _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	void Read();
	virtual void Write();

protected:
	void NewMessage(const String &s);
	byte CalculateCRC(const char *buffer);
	byte CheckCRC(const char *buffer);
	virtual void ProcessCommand(const String &cmd, const String &val);

	String rx;
	String cmd;
	String val;
	String tx;
	HardwareSerial *serial;

};
extern _WDlink WDlink;

