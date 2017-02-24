#pragma once
#include "link.h"
#include "CommandList.h"
class _WDslaveNode : public _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	virtual void Write();

private:
	virtual void ProcessCommand(const String &cmd, const String &val);
	uint8_t aliveCounter;
	bool savePending;
};
extern _WDslaveNode WDslaveNode;