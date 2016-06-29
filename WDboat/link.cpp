#include "link.h"
#include "CommandList.h"
#include "dht11.h"
#include "pins.h"
#include "RGBdriver.h"
#include "EEPROM.h"
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
	savePending = false;
}

enum { SEND_GPS, SEND_IMU, SEND_MISC, SEND_RELAY, SEND_LED };

void _WDlink::Write()
{
	static byte select = 0;
	tx = "$ardu,";
	switch (select)
	{
	case SEND_GPS:
		tx += CommandString[GPS_LAT];
		tx += ",";
		tx += String(MavlinkData.lat, 6);
		tx += ",";

		tx += CommandString[GPS_LON];
		tx += ",";
		tx += String(MavlinkData.lon, 6);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KNOTS];
		tx += ",";
		tx += String(MavlinkData.groundspeed * 1.9438444924574, 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KMH];
		tx += ",";
		tx += String(MavlinkData.groundspeed * 3.6, 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_COURSE];
		tx += ",";
		tx += String(MavlinkData.gps_heading, 2);
		tx += ",";

		tx += CommandString[GPS_X_SPEED];
		tx += ",";
		tx += String(MavlinkData.groundXspeed, 2);
		tx += ",";

		tx += CommandString[GPS_Y_SPEED];
		tx += ",";
		tx += String(MavlinkData.groundYspeed, 2);
		tx += ",";

		tx += CommandString[GPS_NUM_SATS];
		tx += ",";
		tx += "NEI";
    
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
		tx += String(MavlinkData.compassHeading, 0);
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
		tx += String(VoltCurrent.Voltage, 3);
		tx += ",";

		tx += CommandString[CURRENT];
		tx += ",";
		tx += String(VoltCurrent.Current, 3);
		tx += ",";

		tx += CommandString[NODE_ALIVE];
		tx += ",";
		tx += ValueString[WDmasterNode.NodeAlive()];
   
		break;
	case SEND_RELAY:
	{
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
		break;
	}
	case SEND_LED:
		tx += CommandString[LED_RED];
		tx += ",";
		tx += String((int)RGB.r);
		tx += ",";

		tx += CommandString[LED_GREEN];
		tx += ",";
		tx += String((int)RGB.g);
		tx += ",";

		tx += CommandString[LED_BLUE];
		tx += ",";
		tx += String((int)RGB.b);
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
	if (select > SEND_LED)
	{
		select = SEND_GPS;
	}

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

void _WDlink::Read()
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
			buttonLeds[RELAY_BILGE_PP - i].SetOutputs(i, ON);
		}
		else
		{
			buttonLeds[RELAY_BILGE_PP - i].SetOutputs(i, OFF);
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
