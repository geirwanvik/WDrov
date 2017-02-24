#include "master_node.h"
#include "button_led.h"

_WDmasterNode WDmasterNode;

void _WDmasterNode::Init(HardwareSerial *_serial)
{
	talker = "$m";
	slaveTime = 0;
	_WDlink::Init(_serial);
}

enum { SEND_RELAY_1, SEND_RELAY_2 };

void _WDmasterNode::Write()
{
	static byte select = 0;
	tx = talker + ",";

	switch (select)
	{
	case SEND_RELAY_1:
		for (byte i = 0; i < 4; i++)
		{
			byte name = buttonLeds[i].GetName();
			tx += CommandString[name];
			tx += ",";
			tx += ValueString[buttonLeds[i].GetValue()];
			if (i < 3)
			{
				tx += ",";
			}
		}
		break;
	case SEND_RELAY_2:
		for (byte i = 4; i < 8; i++)
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
		break;
	}

	tx += "*";

	byte crc = CalculateCRC(tx.c_str());
	if (crc < 0x10)
	{
		tx += "0";
	}
	tx += String(crc, HEX);

	serial->println(tx);

	select++;
	if (select > SEND_RELAY_2)
	{
		select = SEND_RELAY_1;
	}
}


void _WDmasterNode::ProcessCommand(const String &cmd, const String &val)
{
	int i;
	for (i = 0; i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
	{
		if (cmd == CommandString[i])
		{
			break;
		}
	}

	switch (i)
	{
	case NODE_ALIVE:
		slaveTime = millis();
		break;
	case CURRENT:
	case VOLTAGE:
		WDlink.AddToQueue(cmd, val);
		break;
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