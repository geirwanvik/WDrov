#include "slave_node.h"
#include "relay_output.h"
#include "pins.h"
#include "RGBdriver.h"
#include "EEPROM.h"
_WDslaveNode WDslaveNode;

void _WDslaveNode::Init(HardwareSerial *_serial)
{
	savePending = false;
	_WDlink::Init(_serial);
}

void _WDslaveNode::Write()
{
	tx = "$s,";

	tx += CommandString[NODE_ALIVE];
	tx += ",";
	tx += String(aliveCounter++, 10);

	tx += "*";

	byte crc = CalculateCRC(tx.c_str());
	if (crc < 0x10)
	{
		tx += "0";
	}
	tx += String(crc, HEX);

	serial->println(tx);

	if (savePending)
	{
		savePending = false;
		byte *ptr;
		ptr = (byte*)&RGB;
		for (byte i = 0; i < 6; i++)
		{
			EEPROM.write(0x30 + i, ptr[i]);
		}
	}
}

void _WDslaveNode::ProcessCommand(const String &cmd, const String &val)
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
	case RELAY_BILGE_PP:
	case RELAY_LANTERN:
	case RELAY_WIPER:
	case RELAY_INSTRUMENT:
	case RELAY_5:
	case RELAY_6:
	case RELAY_7:
	case RELAY_8:
		if (val == ValueString[ON])
		{
			RelayOutput[RELAY_BILGE_PP - i].SetOutput(i, ON);
		}
		else
		{
			RelayOutput[RELAY_BILGE_PP - i].SetOutput(i, OFF);
		}
		break;
	case LED_RED:
		RGB.r = val.toInt();
		savePending = true;
		break;
	case LED_GREEN:
		RGB.g = val.toInt();
		savePending = true;
		break;
	case LED_BLUE:
		RGB.b = val.toInt();
		savePending = true;
		break;
	}
}