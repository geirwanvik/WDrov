#include "master_node.h"
#include "button_led.h"

_WDmasterNode WDmasterNode;

void _WDmasterNode::Init(HardwareSerial *_serial)
{
	slaveTime = 0;
	numberOfElements = 0;
	_WDlink::Init(_serial);
}

void _WDmasterNode::Write()
{
	tx = "$m,";

	for (byte i = 0; i < 8; i++)
	{
		byte name = buttonLeds[i].GetName();
		tx += CommandString[name];
		tx += ",";
		tx += ValueString[buttonLeds[i].GetValue()];
		if (i < 7)
		{
			tx += ",";
		}
	}

	tx += "*";

	byte crc = CalculateCRC(tx.c_str());
	if (crc < 0x10)
	{
		tx += "0";
	}
	tx += String(crc, HEX);

	serial->println(tx);
}


void _WDmasterNode::ProcessCommand(const String &cmd, const String &val)
{
	int i;
	CommandEnum cmdEnum;
	for (i = 0; i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
	{
		if (cmd == CommandString[NODE_ALIVE])
		{
			slaveTime = millis();
		}
	}
}

byte _WDmasterNode::NodeAlive()
{
	if (millis() - slaveTime > 1500)
	{
		return false;
	}
	return true;
}

void _WDmasterNode::AddToQueue(const String &cmd, const String &val)
{
	numberOfElements++;
	if (numberOfElements < 4)
	{
		queueCmds[numberOfElements] = cmd;
		queueValues[numberOfElements] = val;

	}
	else
	{
		numberOfElements--;
	}
}

void _WDmasterNode::WriteQueue()
{
	if (numberOfElements == 0)
	{
		return;
	}

	tx = "$m,";

	for (byte i = 0; i < numberOfElements; i++)
	{
		tx += queueCmds[i];
		tx += ",";
		tx += queueValues[i];
		if (i < (numberOfElements -1))
		{
			tx += ",";
		}
	}

	tx += "*";

	byte crc = CalculateCRC(tx.c_str());
	if (crc < 0x10)
	{
		tx += "0";
	}
	tx += String(crc, HEX);

	serial->println(tx);
	numberOfElements = 0;
}