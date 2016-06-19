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

	"IMU_ROLL",
	"IMU_PITCH",
	"IMU_HEADING",
	"ACC_ZERO",
	"MAG_CALIBRATE",

	"DHT22_TEMP",
	"DHT22_HUM",

	"RELAY_BILGE_PP",
	"RELAY_LANTERN",
	"RELAY_WIPER",
	"RELAY_INSTRUMENT",

	"BUTTON_BILGE_PP",
	"BUTTON_LANTERN",
	"BUTTON_WIPER",
	"BUTTON_INSTRUMENT",

    "VOLTAGE",
    "CURRENT",

    "LED_RED",
    "LED_GREEN",
    "LED_BLUE",
	"NODE_ALIVE"
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

    IMU_ROLL,
    IMU_PITCH,
    IMU_HEADING,
    ACC_ZERO,
    MAG_CALIBRATE,

    DHT22_TEMP,
    DHT22_HUM,

    RELAY_BILGE_PP,
    RELAY_LANTERN,
    RELAY_WIPER,
	RELAY_INSTRUMENT,

	BUTTON_BILGE_PP,
	BUTTON_LANTERN,
	BUTTON_WIPER,
	BUTTON_INSTRUMENT,

    VOLTAGE,
    CURRENT,

    LED_RED,
    LED_GREEN,
    LED_BLUE,
	NODE_ALIVE,

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
