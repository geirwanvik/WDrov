#pragma once
#include "link.h"
#include "CommandList.h"

class _WDmasterNode : public _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	virtual void Write();
	void NodeAlive();
	void UpdatePin(CommandEnum pin, byte value);
	byte GetPinState(CommandEnum pin);

private:
	struct PinState
	{
		byte name;
		byte value;
		byte oldValue;
	};
	virtual void ProcessCommand(const String &cmd, const String &val);
	PinState pinState[8];
	byte nodeAlive;

};
extern _WDmasterNode WDmasterNode;
