#pragma once

enum Arduino_Pins
{
	DHT_DATA_PIN		= 41,

	BILGE_PP_PIN		= 42, // Relay 1
	LANTERN_PIN			= 44, // Relay 2
	WIPER_PIN			= 46, // Relay 3
	INSTRUMENT_PIN		= 48, // Relay 4
	RELAY_5				= 43,
	RELAY_6				= 45,
	RELAY_7				= 47,
	RELAY_8				= 49,

	LED_CLK				= 35,
	LED_DATA			= 37,

	CURRENT_SENSOR		= A14,
	VOLTAGE_SENSOR		= A15
};