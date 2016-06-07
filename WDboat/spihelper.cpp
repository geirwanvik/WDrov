#include "spihelper.h"
#include <SPI.h>

#define chipSelect 53
_SpiHelper SpiHelper;

void _SpiHelper::init()
{
	pinMode(chipSelect, OUTPUT);

	// Workaround - spi baro CS pin must be set high else bus is blocked
	pinMode(40, OUTPUT);
	digitalWrite(40, HIGH);

	SPI.begin();
	SPI.setClockDivider(Clock_0_5Mhz);
	SPI.setDataMode(SPI_MODE3);
}

void _SpiHelper::setClockSpeed(ClockSpeeds clock)
{
	SPI.setClockDivider(clock);
}

void _SpiHelper::read(uint8_t reg, uint8_t *buf, uint8_t size)
{
	digitalWrite(chipSelect, LOW);
	SPI.transfer(reg | 0x80);
	for (byte i = 0; i < size; i++)
	{
		*buf = SPI.transfer(0x00);
		buf++;
	}
	digitalWrite(chipSelect, HIGH);
}
void _SpiHelper::write(uint8_t reg, uint8_t val)
{
	digitalWrite(chipSelect, LOW);
	SPI.transfer(reg);
	SPI.transfer(val);
	digitalWrite(chipSelect, HIGH);
}
