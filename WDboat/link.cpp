#include "link.h"
#include "CommandList.h"
#include "imu.h"
#include "dht11.h"
#include "pins.h"
#include "RGBdriver.h"
#include "EEPROM.h"
#include "mpu6050.h"
#include "VoltCurrent.h"
#include "TinyGPS++.h"
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

enum { SEND_GPS, SEND_IMU, SEND_MISC, SEND_BUTTONS, SEND_LED };

void _WDlink::Write()
{
	static byte select = 0;
	tx = "$ardu,";
	switch (select)
	{
	case SEND_GPS:
		tx += CommandString[GPS_LAT];
		tx += ",";
		tx += String(Gps.location.lat(), 6);
		tx += ",";

		tx += CommandString[GPS_LON];
		tx += ",";
		tx += String(Gps.location.lng(), 6);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KNOTS];
		tx += ",";
		tx += String(Gps.speed.knots(), 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_SPEED_KMH];
		tx += ",";
		tx += String(Gps.speed.kmph(), 2);
		tx += ",";

		tx += CommandString[GPS_GROUND_COURSE];
		tx += ",";
		tx += String(Gps.course.deg(), 2);
		tx += ",";

		tx += CommandString[GPS_NUM_SATS];
		tx += ",";
		tx += String(Gps.satellites.value());
		tx += ",";

		tx += CommandString[GPS_HDOP];
		tx += ",";
		tx += String(Gps.hdop.value());
		break;
	case SEND_IMU:
		tx += CommandString[IMU_ROLL];
		tx += ",";
		tx += String(IMU.Roll, 1);
		tx += ",";

		tx += CommandString[IMU_PITCH];
		tx += ",";
		tx += String(IMU.Pitch, 1);
		tx += ",";

		tx += CommandString[IMU_HEADING];
		tx += ",";
		tx += String(IMU.Heading, 1);
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
		break;
	case SEND_BUTTONS:
		tx += CommandString[BUTTON_BILGE_PP];
		tx += ",";
		tx += String(WDmasterNode.GetPinState(BUTTON_BILGE_PP));
		tx += ",";

		tx += CommandString[BUTTON_LANTERN];
		tx += ",";
		tx += String(WDmasterNode.GetPinState(BUTTON_LANTERN));
		tx += ",";

		tx += CommandString[BUTTON_WIPER];
		tx += ",";
		tx += String(WDmasterNode.GetPinState(BUTTON_WIPER));
		tx += ",";

		tx += CommandString[BUTTON_INSTRUMENT];
		tx += ",";
		tx += String(WDmasterNode.GetPinState(BUTTON_INSTRUMENT));
		break;
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

		index = outdex +1;
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
	case ACC_ZERO:
		MPU.calibrateAcc();
		break;
	case MAG_CALIBRATE:
		if (val == ValueString[ON])
		{
			MPU.beginCalibration();
		}
		else
		{
			MPU.endCalibration();
		}
		break;
	case RELAY_BILGE_PP:
		if (val == ValueString[ON])
		{
			digitalWrite(BILGE_PP_PIN, HIGH);
		}
		else
		{
			digitalWrite(BILGE_PP_PIN, LOW);
		}
		WDmasterNode.UpdatePin(BUTTON_BILGE_PP, val.toInt());
		break;
	case RELAY_LANTERN:
		if (val == ValueString[ON])
		{
			digitalWrite(LANTERN_PIN, HIGH);
		}
		else
		{
			digitalWrite(LANTERN_PIN, LOW);
		}
		WDmasterNode.UpdatePin(BUTTON_LANTERN, val.toInt());
		break;
	case RELAY_WIPER:
		if (val == ValueString[ON])
		{
			digitalWrite(WIPER_PIN, HIGH);
		}
		else
		{
			digitalWrite(WIPER_PIN, LOW);
		}
		WDmasterNode.UpdatePin(BUTTON_WIPER, val.toInt());
		break;
	case RELAY_INSTRUMENT:
		if (val == ValueString[ON])
		{
			digitalWrite(INSTRUMENT_PIN, HIGH);
		}
		else
		{
			digitalWrite(INSTRUMENT_PIN, LOW);
		}
		WDmasterNode.UpdatePin(BUTTON_INSTRUMENT, val.toInt());
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
