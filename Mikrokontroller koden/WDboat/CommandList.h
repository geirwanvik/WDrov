#pragma once

#if defined(ARDUINO)
#include "Arduino.h"
#define _String const String
#else
#include <QString>
#define _String const QString
#endif

_String Commands[] =
{
	"GPS_LAT",
	"GPS_LON",
	"GPS_ALT",
	"GPS_GROUND_SPEED",
	"GPS_3D_SPEED",
	"GPS_GROUND_COURSE",
	"GPS_NUM_SATS",
	"GPS_FIX",

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

	"VOLTAGE",
	"CURRENT",

	"LED_RED",
	"LED_GREEN",
	"LED_BLUE"
};

enum Commands
{
	GPS_LAT = 0,
	GPS_LON,
	GPS_ALT,
	GPS_GROUND_SPEED,
	GPS_3D_SPEED,
	GPS_GROUND_COURSE,
	GPS_NUM_SATS,
	GPS_FIX,

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

	VOLTAGE,
	CURRENT,

	LED_RED,
	LED_GREEN,
	LED_BLUE
};

_String Values[] =
{
	"OFF",
	"ON",
	"STATUS"
};

enum Values
{
	OFF = 0,
	ON,
	STATUS
};