#include "Arduino.h"
#include <EEPROM.h>
#include "dht11.h"
#include "link.h"
#include "pins.h"
#include "VoltCurrent.h"
#include "RGBdriver.h"
#include "button_led.h"
#include "CommandList.h"
#include "MavlinkParser.h"

void setup()
{
	WDlink.Init(&Serial);
	MavlinkParser.Init(&Serial2);
	DHT.Init(DHT_DATA_PIN);
	VoltCurrent.Init();
	Driver.Init(LED_CLK, LED_DATA);

	buttonLeds[0].Init(RELAY_BILGE_PP, BUTTON_BILGE_PIN, LED_BILGE_PIN, RELAY_BILGE_PP_PIN);
	buttonLeds[1].Init(RELAY_LANTERN, BUTTON_LANTERN_PIN, LED_LANTERN_PIN, RELAY_LANTERN_PIN);
	buttonLeds[2].Init(RELAY_WIPER, BUTTON_WIPER_PIN, LED_WIPER_PIN, RELAY_WIPER_PIN);
	buttonLeds[3].Init(RELAY_INSTRUMENT, BUTTON_INSTRUMENT_PIN, LED_INSTRUMENT_PIN, RELAY_INSTRUMENT_PIN);

	buttonLeds[4].Init(RELAY_SPARE5, BUTTON_5_PIN, LED_5_PIN, RELAY_5);
	buttonLeds[5].Init(RELAY_SPARE6, BUTTON_6_PIN, LED_6_PIN, RELAY_6);
	buttonLeds[6].Init(RELAY_SPARE7, BUTTON_7_PIN, LED_7_PIN, RELAY_7);
	buttonLeds[7].Init(RELAY_SPARE8, BUTTON_8_PIN, LED_8_PIN, RELAY_8);

	RGB_STATE load;
	byte *ptr;
	ptr = (byte*)&load;

	for (byte i = 0; i < 6; i++)
	{
		ptr[i] = EEPROM.read(0x30 + i);
	}
	memcpy(&RGB, &load, sizeof(RGB_STATE));
}

uint32_t updateSlowLoop = 0;
uint32_t updateFastLoop = 0;

void loop()
{
	WDlink.Read();
	MavlinkParser.Read();

	for (byte i = 0; i < 8; i++)
	{
		buttonLeds[i].ReadButton();
	}

	//int red = 128 + 127 * cos(2 * PI / RGB.fade * (millis()));

	Driver.begin(); // begin
	Driver.SetColor(RGB.r, RGB.g, RGB.b); //Red. first node data
	Driver.end();

	if ((millis() - updateSlowLoop) >= 1000)
	{
		updateSlowLoop = millis();
		DHT.Update();
	}
	else if ((millis() - updateFastLoop) >= 100)
	{
		updateFastLoop = millis();
		VoltCurrent.Update();
		WDlink.Write();
	}
}
