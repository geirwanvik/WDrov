#include "Arduino.h"
#include <SPI.h>
#include <EEPROM.h>
#include "imu.h"
#include "dht11.h"
#include "gps_ublox.h"
#include "link.h"
#include "pins.h"
#include "VoltCurrent.h"
#include "RGBdriver.h"

RGBdriver Driver(LED_CLK, LED_DATA);

RGB_STATE RGB;



void setup()
{
	WDlink.Init();
	IMU.Init();
	DHT.Init(DHT_DATA_PIN);
	GPS.Init();
	VoltCurrent.Init();

	digitalWrite(BILGE_PP_PIN, LOW);
	pinMode(BILGE_PP_PIN, OUTPUT);


	digitalWrite(LANTERN_PIN, LOW);
	pinMode(LANTERN_PIN, OUTPUT);


	digitalWrite(WIPER_PIN, LOW);
	pinMode(WIPER_PIN, OUTPUT);

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
uint32_t delayImuLoop = 0;

void loop()
{
	delayImuLoop = millis();
	IMU.Update();
	WDlink.Read();

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
		GPS.Read();
		if (GPS.NewData)
		{
			GPS.NewData = 0;
		}
		WDlink.Write();
	}
	
	if ((millis() - delayImuLoop) < 3)
	{
		delay(millis() - delayImuLoop);
	}
}
