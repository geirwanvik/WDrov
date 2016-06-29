#pragma once
#include "Arduino.h"
class _WDslaveNode
{
public:
	void Init(HardwareSerial *_serial);
	void Read();
	void Write();
	byte MasterAlive();

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
	uint32_t slaveTime;
	uint32_t masterTime;
	byte aliveCounter;
};
extern _WDslaveNode WDslaveNode;
