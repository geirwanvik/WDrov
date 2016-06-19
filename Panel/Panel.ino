#include "slave_node.h"
#include "pins.h"
void setup()
{
	digitalWrite(LED_BILGE_PIN, LOW);
	pinMode(LED_BILGE_PIN, OUTPUT);
	pinMode(LED_LANTERN_PIN, OUTPUT);
	digitalWrite(LED_LANTERN_PIN, LOW);
	pinMode(LED_WIPER_PIN, OUTPUT);
	digitalWrite(LED_WIPER_PIN, LOW);
	pinMode(LED_INSTRUMENT_PIN, OUTPUT);
	digitalWrite(LED_INSTRUMENT_PIN, LOW);
	pinMode(LED_5_PIN, OUTPUT);
	digitalWrite(LED_5_PIN, LOW);
	pinMode(LED_6_PIN, OUTPUT);
	digitalWrite(LED_6_PIN, LOW);
	pinMode(LED_7_PIN, OUTPUT);
	digitalWrite(LED_7_PIN, LOW);
	pinMode(LED_8_PIN, OUTPUT);
	digitalWrite(LED_8_PIN, LOW);

	pinMode(BUTTON_BILGE_PIN, INPUT);
	pinMode(BUTTON_LANTERN_PIN, INPUT);
	pinMode(BUTTON_WIPER_PIN, INPUT);
	pinMode(BUTTON_INSTRUMENT_PIN, INPUT);
	pinMode(BUTTON_5_PIN, INPUT);
	pinMode(BUTTON_6_PIN, INPUT);
	pinMode(BUTTON_7_PIN, INPUT);
	pinMode(BUTTON_8_PIN, INPUT);

	WDslaveNode.Init(&Serial);
}

void loop()
{
	// TODO - ADD ANTI BOUNCE ON BUTTON
	// ADD PUSH FOR ON, PUSH AGAIN FOR OFF
	// ADD ALL LED BLINK IF NO COMM
	WDslaveNode.Read();
	for (byte i = BUTTON_BILGE_PIN; i < LED_BILGE_PIN; i++)
	{
		WDslaveNode.SetPinState(i, digitalRead(i));
	}

	WDslaveNode.Write();

}
