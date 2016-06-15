#pragma once

#include "Arduino.h"
#include "CommandList.h"

class _WDlink
{
public:
	void Init();
	void Read();
	void Write();

private:
	void NewMessage(const String &s);
	byte CalculateCRC(const char *buffer);
	byte CheckCRC(const char *buffer);
	void ProcessCommand(const String &cmd, const String &val);
	String tx;
	String rx;
	String cmd;
	String val;
	bool savePending;
};
extern _WDlink WDlink;

