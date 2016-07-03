#include "link.h"
#include "CommandList.h"
#include "dht11.h"
#include "pins.h"
#include "VoltCurrent.h"
#include "button_led.h"
#include "MavlinkParser.h"
#include "master_node.h"
_WDlink WDlink;

void _WDlink::Init(HardwareSerial *_serial)
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
}

enum { SEND_GPS_1, SEND_GPS_2, SEND_IMU, SEND_MISC, SEND_RELAY_1, SEND_RELAY_2 };

void _WDlink::Write()
{
	static byte select = 0;
	tx = "$ardu,";
	switch (select)
	{
	case SEND_GPS_1:
		tx += CommandString[GPS_LAT];
		tx += ",";
		tx += String(MavlinkData.lat, 6);
		tx += ",";

		tx += CommandString[GPS_LON];
		tx += ",";
		tx += String(MavlinkData.lon, 6);
		tx += ",";

		tx += CommandString[GPS_GROUND_COURSE];
		tx += ",";
		tx += String(MavlinkData.gps_heading, 2);
		break;
	case SEND_GPS_2:

		tx += CommandString[GPS_X_SPEED];
		tx += ",";
		tx += String(MavlinkData.groundXspeed, 2);
		tx += ",";

		tx += CommandString[GPS_Y_SPEED];
		tx += ",";
		tx += String(MavlinkData.groundYspeed, 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KNOTS];
		tx += ",";
		tx += String(MavlinkData.groundspeed * 1.9438444924574, 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KMH];
		tx += ",";
		tx += String(MavlinkData.groundspeed * 3.6, 2);
		break;

	case SEND_IMU:
		tx += CommandString[IMU_ROLL];
		tx += ",";
		tx += String(MavlinkData.roll, 1);
		tx += ",";

		tx += CommandString[IMU_PITCH];
		tx += ",";
		tx += String(MavlinkData.pitch, 1);
		tx += ",";

		tx += CommandString[IMU_HEADING];
		tx += ",";
		tx += String(MavlinkData.compassHeading);
		tx += ",";

		tx += CommandString[IMU_RATE_OF_TURN];
		tx += ",";
		tx += String(MavlinkData.yawSpeed, 2);
		break;
	case SEND_MISC:
		tx += CommandString[DHT22_TEMP];
		tx += ",";
		tx += String(DHT.Temperature, 1);
		tx += ",";

		tx += CommandString[DHT22_HUM];
		tx += ",";
		tx += String(DHT.Humidity, 1);
		tx += ",";

		tx += CommandString[VOLTAGE];
		tx += ",";
		tx += WDmasterNode.Voltage;
		tx += ",";

		tx += CommandString[CURRENT];
		tx += ",";
		tx += WDmasterNode.Current;
		tx += ",";

		tx += CommandString[NODE_ALIVE];
		tx += ",";
		tx += ValueString[WDmasterNode.NodeAlive()];
		break;
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
		select = SEND_GPS_1;
	}
}

void _WDlink::Read()
{
	while (serial->available())
	{
		char data = serial->read();

		if ((data == '\n') || (data == '\r') || (data == '$'))
		{
			if (rx.length() < 3)
			{
				rx = "";
				if (data == '$')
				{
					rx.concat(data);
				}
				return;
			}
			byte crcOK = CheckCRC(rx.c_str());
			if (crcOK)
			{
				NewMessage(rx);
			}
			rx = "";
			if (data == '$')
			{
				rx.concat(data);
			}
		}
		else
		{
			rx.concat(data);
		}
	}
}

void _WDlink::NewMessage(const String &s)
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

void _WDlink::ProcessCommand(const String &cmd, const String &val)
{
	int i;
	byte value;
	for (i = 0; i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
	{
		if (cmd == CommandString[i])
		{
			break;
		}
	}

	if (val == ValueString[ON])
	{
		value = ON;
	}
	else
	{
		value = OFF;
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
	case BUTTON_LED:
		for (byte j = 0; j < 8; j++)
		{
			if (buttonLeds[j].CommandReceived(i, value))
			{
				break;
			}
		}
		WDmasterNode.AddToQueue(cmd, val);
		break;
	case LED_RED:
	case LED_GREEN:
	case LED_BLUE:
		WDmasterNode.AddToQueue(cmd, val);
		break;
	}
}

byte _WDlink::CalculateCRC(const char *buffer)
{
	byte c = 0;
	buffer++;
	while (*buffer != '*')
	{
		c ^= *buffer++;
	}
	return c;
}

byte _WDlink::CheckCRC(const char *buffer)
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
