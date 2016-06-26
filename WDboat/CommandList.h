#pragma once

#if defined(ARDUINO)
#include "Arduino.h"
#define _String const String
#else
#include <QString>
#define _String const QString
#endif

_String CommandString[] =
{
	"GPS_LAT",
	"GPS_LON",
	"GPS_GROUND_SPEED_KNOTS",
	"GPS_GROUND_SPEED_KMH",
	"GPS_GROUND_COURSE",
	"GPS_NUM_SATS",
	"GPS_HDOP",
	"GPS_X_SPEED", //Ground X Speed (Latitude, positive north) m/s
	"GPS_Y_SPEED", //Ground Y Speed (Longitude, positive east) m/s

	"IMU_ROLL",
	"IMU_PITCH",
	"IMU_HEADING",
	"IMU_RATE_OF_TURN", // DEG/SEC

	"DHT22_TEMP",
	"DHT22_HUM",

	"RELAY_BILGE_PP",
	"RELAY_LANTERN",
	"RELAY_WIPER",
	"RELAY_INSTRUMENT",
	"RELAY_SPARE5",
	"RELAY_SPARE6",
	"RELAY_SPARE7",
	"RELAY_SPARE8",

  "VOLTAGE",
  "CURRENT",

  "LED_RED",
  "LED_GREEN",
  "LED_BLUE"
};

enum CommandEnum
{
    GPS_LAT = 0,
    GPS_LON,
	GPS_GROUND_SPEED_KNOTS,
	GPS_GROUND_SPEED_KMH,
    GPS_GROUND_COURSE,
    GPS_NUM_SATS,
	GPS_HDOP,
	GPS_X_SPEED,
	GPS_Y_SPEED,

    IMU_ROLL,
    IMU_PITCH,
    IMU_HEADING,
	IMU_RATE_OF_TURN,

    DHT22_TEMP,
    DHT22_HUM,

    RELAY_BILGE_PP,
    RELAY_LANTERN,
    RELAY_WIPER,
	RELAY_INSTRUMENT,
	RELAY_SPARE5,
	RELAY_SPARE6,
	RELAY_SPARE7,
	RELAY_SPARE8,

    VOLTAGE,
    CURRENT,

    LED_RED,
    LED_GREEN,
    LED_BLUE,

	UNUSED = 0xff
};

_String ValueString[] =
{
    "OFF",
    "ON",
    "STATUS"
};

enum ValueEnum
{
    OFF = 0,
    ON,
    STATUS
};
