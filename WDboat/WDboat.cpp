#include "WDboat.h"
#include <EEPROM.h>
#include "dht11.h"
#include "link.h"
#include "pins.h"
#include "VoltCurrent.h"
#include "RGBdriver.h"
#include "button_led.h"
#include "CommandList.h"
#include "MavlinkParser.h"
#include "master_node.h"
#include "slave_node.h"
#include "relay_output.h"

#define BRIDGE	1
#define AFT 2

#define CONTROLLER BRIDGE
//#define CONTROLLER AFT


inline bool isBridge() { if (CONTROLLER == BRIDGE) { return true; } return false; };
inline bool isAft() { if (CONTROLLER == AFT) { return true; } return false; };

void setup()
{
	if (isBridge())
	{
		WDlink.Init(&Serial);			// UART 0
		MavlinkParser.Init(&Serial1);	// UART 1
		WDmasterNode.Init(&Serial2);	// UART 2

		buttonLeds[0].Init(RELAY_BILGE_PP, BUTTON_BILGE_PIN, LED_BILGE_PIN);
		buttonLeds[1].Init(RELAY_LANTERN, BUTTON_LANTERN_PIN, LED_LANTERN_PIN);
		buttonLeds[2].Init(RELAY_WIPER, BUTTON_WIPER_PIN, LED_WIPER_PIN);
		buttonLeds[3].Init(RELAY_INSTRUMENT, BUTTON_INSTRUMENT_PIN, LED_INSTRUMENT_PIN);

		buttonLeds[4].Init(RELAY_SPARE5, BUTTON_5_PIN, LED_5_PIN);
		buttonLeds[5].Init(RELAY_SPARE6, BUTTON_6_PIN, LED_6_PIN);
		buttonLeds[6].Init(RELAY_SPARE7, BUTTON_7_PIN, LED_7_PIN);
		buttonLeds[7].Init(LED_STATUS, BUTTON_8_PIN, LED_8_PIN);

		DHT.Init(DHT_DATA_PIN);
	}
	else
	{
		RelayOutput[0].Init(RELAY_BILGE_PP, RELAY_BILGE_PP_PIN);
		RelayOutput[1].Init(RELAY_LANTERN, RELAY_LANTERN_PIN);
		RelayOutput[2].Init(RELAY_WIPER, RELAY_WIPER_PIN);
		RelayOutput[3].Init(RELAY_INSTRUMENT, RELAY_INSTRUMENT_PIN);

		RelayOutput[4].Init(RELAY_SPARE5, RELAY_5);
		RelayOutput[5].Init(RELAY_SPARE6, RELAY_6);
		RelayOutput[6].Init(RELAY_SPARE7, RELAY_7);
		RelayOutput[7].Init(RELAY_SPARE8, RELAY_8);

		WDslaveNode.Init(&Serial1);
		VoltCurrent.Init();
		Driver.Init(LED_CLK, LED_DATA);

		RGB_STATE load;
		byte *ptr;
		ptr = (byte*)&load;

		for (byte i = 0; i < 6; i++)
		{
			ptr[i] = EEPROM.read(0x30 + i);
		}
		memcpy(&RGB, &load, sizeof(RGB_STATE));
	}
}

uint32_t updateSlowLoop = 0;
uint32_t updateFastLoop = 0;

inline void BridgeLoop()
{
	byte sendButtonsNow = false;
	WDlink.Read();
	MavlinkParser.Read();
	WDmasterNode.Read();
	for (byte i = 0; i < 8; i++)
	{
		if (WDmasterNode.NodeAlive())
		{
			buttonLeds[i].ReadButton();
			if (buttonLeds[i].ButtonChanged())
				sendButtonsNow = true;
		}
		else
		{
			buttonLeds[i].Blink();
		}

	}
	if ((millis() - updateFastLoop) >= 100)
	{
		updateFastLoop = millis();
		if (!WDlink.WriteQueue())
		{
			WDlink.Write();
		}
		WDmasterNode.WriteQueue();
	}
	if (sendButtonsNow || ((millis() - updateSlowLoop) >= 1000))
	{
		DHT.Update();
		WDmasterNode.Write();
		updateSlowLoop = millis();
	}
}
RGB_STATE prevRGB = { 0, 0, 0, 0};
inline void AftLoop()
{
	WDslaveNode.Read();

	if ((RGB.r != prevRGB.r) || (RGB.g != prevRGB.g) || (RGB.b != prevRGB.b) || (RGB.state != prevRGB.state))
	{
		Driver.begin(); // begin
		if (RGB.state)
		{
			Driver.SetColor(RGB.r, RGB.g, RGB.b); //Red. first node data
		}
		else
		{
			Driver.SetColor(0, 0, 0); //Red. first node data
		}
		Driver.end();
		prevRGB = RGB;
	}

	if ((millis() - updateSlowLoop) >= 1000)
	{
		updateSlowLoop = millis();
		WDslaveNode.Write();
	}
	else if ((millis() - updateFastLoop) >= 100)
	{
		VoltCurrent.Update();
		updateFastLoop = millis();
	}
}

void loop()
{
	if (isBridge())
	{
		BridgeLoop();
	}
	else
	{
		AftLoop();
	}
}
