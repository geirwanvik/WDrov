#pragma once

const String CommandString[] =
{
	"BUTTON_BILGE_PP",
	"BUTTON_LANTERN",
	"BUTTON_WIPER",
	"BUTTON_INSTRUMENT",
	"NODE_ALIVE"
};

enum CommandEnum
{
	BUTTON_BILGE_PP,
	BUTTON_LANTERN,
	BUTTON_WIPER,
	BUTTON_INSTRUMENT,
	NODE_ALIVE,

	UNUSED = 0xff
};

const String ValueString[] =
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

enum Arduino_Pins
{
	BUTTON_BILGE_PIN	= A0,
	BUTTON_LANTERN_PIN  = A1,
	BUTTON_WIPER_PIN	= A2,
	BUTTON_INSTRUMENT_PIN = A3,
	BUTTON_5_PIN		= A4,
	BUTTON_6_PIN		= A5,
	BUTTON_7_PIN		= A6,
	BUTTON_8_PIN		= A7,
	LED_BILGE_PIN		= 12, // Out 1
	LED_LANTERN_PIN		= 11, // Out 2
	LED_WIPER_PIN		= 8, // Out 3
	LED_INSTRUMENT_PIN  = 7, // Out 4
	LED_5_PIN			= 6, // Out 5
	LED_6_PIN			= 3, // Out 6
	LED_7_PIN			= 2, // Out 7
	LED_8_PIN			= 5 // Out 8
};