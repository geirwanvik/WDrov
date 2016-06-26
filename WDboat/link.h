#pragma once

#include "Arduino.h"

class _WDlink
{
public:
	void Init(HardwareSerial *_serial);
	void Read();
	void Write();

private:
	void NewMessage(const String &s);
	byte CalculateCRC(const char *buffer);
	byte CheckCRC(const char *buffer);
	void ProcessCommand(const String &cmd, const String &val);

	String rx;
	String cmd;
	String val;
	bool savePending;
	String tx;
	HardwareSerial *serial;

};
extern _WDlink WDlink;

