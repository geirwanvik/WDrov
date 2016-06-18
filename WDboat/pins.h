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
//
//enum Arduino_Slave_Pins
//{
//	BUTTON_BILGE_PIN	= 2,
//	BUTTON_LANTERN_PIN  = 3,
//	BUTTON_WIPER_PIN	= 4,
//	BUTTON_INSTRUMENT_PIN = 5,
//	BUTTON_5_PIN		= 6,
//	BUTTON_6_PIN		= 7,
//	BUTTON_8_PIN		= 8,
//	LED_BILGE_PIN		= 9,
//	LED_LANTERN_PIN		= 10,
//	LED_WIPER_PIN		= 11,
//	LED_INSTRUMENT_PIN  = 12,
//	LED_5_PIN			= A0,
//	LED_6_PIN			= A1,
//	LED_7_PIN			= A2,
//	LED_8_PIN			= A3
//};