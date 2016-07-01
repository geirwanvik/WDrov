#pragma once
#include "link.h"
#include "CommandList.h"

class _WDmasterNode : public _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	virtual void Write();
	byte NodeAlive();
	void AddToQueue(const String &cmd, const String &val);
	void WriteQueue();

private:
	virtual void ProcessCommand(const String &cmd, const String &val);
	uint32_t slaveTime;
	byte numberOfElements;
	String queueValues[4];
	String queueCmds[4];
};
extern _WDmasterNode WDmasterNode;
