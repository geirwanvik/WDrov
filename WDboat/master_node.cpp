#include "master_node.h"
_WDmasterNode WDmasterNode;

void _WDmasterNode::Init(HardwareSerial *_serial)
{
	for (byte i = 0; i < 8; i++)
	{
		pinState[i].value = 0;
		pinState[i].oldValue = 128;
		pinState[i].name = UNUSED;
	}
	pinState[0].name = BUTTON_BILGE_PP;
	pinState[1].name = BUTTON_LANTERN;
	pinState[2].name = BUTTON_WIPER;
	pinState[3].name = BUTTON_INSTRUMENT;

	slaveTime = 0;
	masterTime = 0;
	aliveCounter = 0;
	_WDlink::Init(_serial);
}

void _WDmasterNode::UpdatePin(CommandEnum pin, byte value)
{
	for (byte i = 0; i < 8; i++)
	{
		if (pinState[i].name == pin)
		{
			pinState[i].value = value;
			return;
		}
	}
}

byte _WDmasterNode::GetPinState(CommandEnum pin)
{
	for (byte i = 0; i < 8; i++)
	{
		if (pinState[i].name == pin)
		{
			return pinState[i].value;
		}
	}
	return UNUSED;
}

void _WDmasterNode::Write()
{
	tx = "$master,";

	for (byte i = 0; i < 8; i++)
	{
		if ((pinState[i].value != pinState[i].oldValue) && (pinState[i].name != UNUSED))
		{
			pinState[i].oldValue = pinState[i].value;
			tx += CommandString[pinState[i].name];
			tx += ",";
			tx += String(pinState[i].value);
			tx += ",";
		}
	}

	if ((millis() - masterTime) > 1000)
	{
		masterTime = millis();
		tx += CommandString[NODE_ALIVE];
		tx += ",";
		tx += String(aliveCounter++,10);
		tx += ",";
	}

	if (tx.compareTo("$master,") == 0)
	{
		return; // No pin change this loop
	}

	tx.remove(tx.length() - 1);
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
		else if (cmd == CommandString[i])
		{
			cmdEnum = static_cast<CommandEnum>(i);
			for (byte j = 0; j < 8; j++)
			{
				if (pinState[j].name == cmdEnum)
				{
					if (val == ValueString[ON])
					{
						pinState[j].value = pinState[j].oldValue = 1;
					}
					else
					{
						pinState[j].value = pinState[j].oldValue = 0;
					}

					return;
				}
			}
			break;
		}
	}
}

byte _WDmasterNode::NodeAlive()
{
	if (millis() - slaveTime > 1100)
	{
		return false;
	}
	return true;
}