#include "slave_node.h"
#include "button_led.h"
#include "pins.h"

void setup()
{
	WDslaveNode.Init(&Serial);
	buttonLeds[0].Init(BUTTON_BILGE_PP, BUTTON_BILGE_PIN, LED_BILGE_PIN);
	buttonLeds[1].Init(BUTTON_LANTERN, BUTTON_LANTERN_PIN, LED_LANTERN_PIN);
	buttonLeds[2].Init(BUTTON_WIPER, BUTTON_WIPER_PIN, LED_WIPER_PIN);
	buttonLeds[3].Init(BUTTON_INSTRUMENT, BUTTON_INSTRUMENT_PIN, LED_INSTRUMENT_PIN);

	buttonLeds[4].Init(UNUSED, BUTTON_5_PIN, LED_5_PIN);
	buttonLeds[5].Init(UNUSED, BUTTON_6_PIN, LED_6_PIN);
	buttonLeds[6].Init(UNUSED, BUTTON_7_PIN, LED_7_PIN);
	buttonLeds[7].Init(UNUSED, BUTTON_8_PIN, LED_8_PIN);
}

void loop()
{
	WDslaveNode.Read();

	for (byte i = 0; i < 8; i++)
	{
		if (WDslaveNode.MasterAlive())
		{
			buttonLeds[i].ReadButton();
		}
		else
		{
			buttonLeds[i].Blink();
		}
	}

	WDslaveNode.Write();
}
