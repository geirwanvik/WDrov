#include "link.h"
#include "CommandList.h"
#include "imu.h"
#include "dht11.h"
#include "gps_ublox.h"
#include "pins.h"
#include "RGBdriver.h"
#include "EEPROM.h"
#ifdef USE_MPU600
#include "mpu6000.h"
#else
#include "mpu6050.h"
#endif
#include "VoltCurrent.h"

_WDlink WDlink;

void _WDlink::Init()
{
	Serial.begin(115200);
	tx.reserve(100);
	rx.reserve(100);
	rx = "";
	cmd.reserve(20);
	cmd = "";
	val.reserve(20);
	val = "";
	savePending = false;
}

enum { SEND_GPS, SEND_IMU, SEND_MISC, SEND_LED };

void _WDlink::Write()
{
	static byte select = 0;
	byte ret;
	tx = "$ardu,";
	switch (select)
	{
	case SEND_GPS:
		tx += Commands[GPS_LAT];
		tx += ",";
		tx += String((double)(GPS.Lattitude / 10000000.0), 7);
		tx += ",";

		tx += Commands[GPS_LON];
		tx += ",";
		tx += String((double)(GPS.Longitude / 10000000.0), 7);
		tx += ",";

		tx += Commands[GPS_ALT];
		tx += ",";
		tx += String((double)(GPS.Altitude / 100.0), 2);
		tx += ",";

		tx += Commands[GPS_GROUND_SPEED];
		tx += ",";
		tx += String((double)(GPS.Ground_Speed / 100.0), 2);
		tx += ",";

		tx += Commands[GPS_3D_SPEED];
		tx += ",";
		tx += String((double)(GPS.Speed_3d / 100.0), 2);
		tx += ",";

		tx += Commands[GPS_GROUND_COURSE];
		tx += ",";
		tx += String((double)(GPS.Ground_Course / 100.0), 2);
		tx += ",";

		tx += Commands[GPS_NUM_SATS];
		tx += ",";
		tx += GPS.NumSats;
		tx += ",";

		tx += Commands[GPS_FIX];
		tx += ",";
		tx += GPS.Fix;
		break;
	case SEND_IMU:
		tx += Commands[IMU_ROLL];
		tx += ",";
		tx += String(IMU.Roll, 1);
		tx += ",";

		tx += Commands[IMU_PITCH];
		tx += ",";
		tx += String(IMU.Pitch, 1);
		tx += ",";

		tx += Commands[IMU_HEADING];
		tx += ",";
		tx += String(IMU.Heading, 1);
		break;
	case SEND_MISC:
		tx += Commands[DHT22_TEMP];
		tx += ",";
		tx += String(DHT.Temperature, 1);
		tx += ",";

		tx += Commands[DHT22_HUM];
		tx += ",";
		tx += String(DHT.Humidity, 1);
		tx += ",";

		tx += Commands[VOLTAGE];
		tx += ",";
		tx += String(VoltCurrent.Voltage, 3);
		tx += ",";

		tx += Commands[CURRENT];
		tx += ",";
		tx += String(VoltCurrent.Current, 3);
		break;
	case SEND_LED:
		tx += Commands[LED_RED];
		tx += ",";
		tx += String((int)RGB.r);
		tx += ",";

		tx += Commands[LED_GREEN];
		tx += ",";
		tx += String((int)RGB.g);
		tx += ",";

		tx += Commands[LED_BLUE];
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

	Serial.println(tx);

	select++;
	if (select > SEND_LED)
	{
		select = SEND_GPS;
	}
}

void _WDlink::Read()
{
	while (Serial.available())
	{
		char data = Serial.read();
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

void _WDlink::ProcessCommand(const String &cmd, const String &val)
{
	int i;
	for (i = 0; i < sizeof(Commands) / sizeof(Commands[0]); i++)
	{
		if (cmd == Commands[i])
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
		if (val == "ON")
		{
			MPU.beginCalibration();
		}
		else
		{
			MPU.endCalibration();
		}
		break;
	case RELAY_BILGE_PP:
		if (val == "ON")
		{
			digitalWrite(BILGE_PP_PIN, HIGH);
		}
		else
		{
			digitalWrite(BILGE_PP_PIN, LOW);
		}
		break;
	case RELAY_LANTERN:
		if (val == "ON")
		{
			digitalWrite(LANTERN_PIN, HIGH);
		}
		else
		{
			digitalWrite(LANTERN_PIN, LOW);
		}
		break;
	case RELAY_WIPER:
		if (val == "ON")
		{
			digitalWrite(WIPER_PIN, HIGH);
		}
		else
		{
			digitalWrite(WIPER_PIN, LOW);
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
