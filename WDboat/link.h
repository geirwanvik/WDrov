#pragma once

#include "Arduino.h"

class _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	void Read();
	virtual void Write();
	void AddToQueue(const String &cmd, const String &val);
	bool WriteQueue();

protected:
	void NewMessage(const String &s);
	byte CalculateCRC(const char *buffer);
	byte CheckCRC(const char *buffer);
	virtual void ProcessCommand(const String &cmd, const String &val);

	String talker;
	String rx;
	String cmd;
	String val;
	String tx;
	String qTx;
	HardwareSerial *serial;

};
extern _WDlink WDlink;

