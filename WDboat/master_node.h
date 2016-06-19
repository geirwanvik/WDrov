#pragma once
#include "link.h"
#include "CommandList.h"

class _WDmasterNode : public _WDlink
{
public:
	virtual void Init(HardwareSerial *_serial);
	virtual void Write();
	byte NodeAlive();
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
	uint32_t slaveTime;
	uint32_t masterTime;
	byte aliveCounter;

};
extern _WDmasterNode WDmasterNode;
