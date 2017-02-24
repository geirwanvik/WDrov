#pragma once
#include "link.h"
#include "CommandList.h"

class _WDmasterNode : public _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	virtual void Write();
	byte NodeAlive();

private:
	virtual void ProcessCommand(const String &cmd, const String &val);
	uint32_t slaveTime;
};
extern _WDmasterNode WDmasterNode;
