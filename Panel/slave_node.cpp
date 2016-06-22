#include "slave_node.h"
#include "button_led.h"
#include "pins.h"

_WDslaveNode WDslaveNode;

void _WDslaveNode::Init(HardwareSerial *_serial)
{
	serial = _serial;
	serial->begin(115200);
	tx.reserve(100);
	rx.reserve(100);
	rx = "";
	cmd.reserve(20);
	cmd = "";
	val.reserve(20);
	val = "";
	savePending = false;

	slaveTime = 0;
	masterTime = 0;
	aliveCounter = 0;
}

enum { SEND_GPS, SEND_IMU, SEND_MISC, SEND_BUTTONS, SEND_LED };

void _WDslaveNode::Write()
{
	tx = "$slave,";

	for (byte i = 0; i < 8; i++)
	{
		if ((buttonLeds[i].GetName() != UNUSED) && (buttonLeds[i].ButtonChanged()))
		{
			tx += CommandString[buttonLeds[i].GetName()];
			tx += ",";
			tx += String(buttonLeds[i].GetValue());
			tx += ",";
		}
	}

	if ((millis() - slaveTime) > 1000)
	{
		slaveTime = millis();
		tx += CommandString[NODE_ALIVE];
		tx += ",";
		tx += String(aliveCounter++, 10);
		tx += ",";
	}

	if (tx.compareTo("$slave,") == 0)
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

void _WDslaveNode::Read()
{
	while (serial->available())
	{
		char data = serial->read();
		if ((data != '\n') && (data != '\r'))
		{
			rx.concat(data);
		}
		else
		{
			byte crcOK = CheckCRC(rx.c_str());
			if (crcOK)
			{
				NewMessage(rx);
			}
			rx = "";
		}
	}
}

void _WDslaveNode::NewMessage(const String &s)
{
	int index = 0, outdex = 0;
	byte numElements = 0, i = 0;
	const char delim = ',';
	const char stop = '*';

	while (1)
	{
		index = s.indexOf(delim, index);
		if (index == -1)
		{
			break;
		}
		index++;
		numElements++;
	};
	numElements /= 2;

	index = outdex = 0;

	for (i = 0; i < numElements; i++)
	{
		index = s.indexOf(delim, index);
		index++;
		outdex = s.indexOf(delim, index);
		cmd = s.substring(index, outdex);

		index = outdex + 1;
		outdex = s.indexOf(delim, index);
		val = s.substring(index, outdex);
		index = outdex;

		if (val.indexOf(stop) != -1)
		{
			index = val.indexOf(stop);
			val.remove(index, 3);
		}
		ProcessCommand(cmd, val);
	}
}

void _WDslaveNode::ProcessCommand(const String &cmd, const String &val)
{
	int i;
	CommandEnum cmdEnum;
	byte value;
	for (i = 0; i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
	{
		if (cmd == CommandString[NODE_ALIVE])
		{
			masterTime = millis();
		}
		else if (cmd == CommandString[i])
		{
			cmdEnum = static_cast<CommandEnum>(i);
			if (val == ValueString[ON])
			{
				value = 1;
			}
			else
			{
				value = 0;
			}
			for (byte j = 0; j < 8; j++)
			{
				buttonLeds[j].SetLed(cmdEnum, value);
			}
			break;
		}
	}
}

byte _WDslaveNode::CalculateCRC(const char *buffer)
{
	byte c = 0;
	buffer++;
	while (*buffer != '*')
	{
		c ^= *buffer++;
	}
	return c;
}

byte _WDslaveNode::CheckCRC(const char *buffer)
{
	byte c = 0;
	byte crc = 0;
	buffer++;
	while (*buffer != '*')
	{
		c ^= *buffer++;
	}
	buffer++;
	crc = strtoul(buffer, 0, 16);
	if (c == crc)
	{
		return true;
	}
	return false;
}

byte _WDslaveNode::MasterAlive()
{
	if ((millis() - masterTime) > 1100)
	{
		return false;
	}
	return true;
}

