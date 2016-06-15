#pragma once
#include "Arduino.h"

enum ClockSpeeds { Clock_8Mhz = 0x04, Clock_4Mhz = 0x00, Clock_2Mhz = 0x05, Clock_1Mhz = 0x1, Clock_0_5Mhz = 0x06, Clock_0_25Mhz = 0x02, Clock_0_125Mhz = 0x03 };

class _SpiHelper
{
public:
	 void init(void);
	 void setClockSpeed(ClockSpeeds clock);
	 void read(uint8_t reg, uint8_t *buf, uint8_t size);
	 void write(uint8_t reg, uint8_t val);
};
extern _SpiHelper SpiHelper;
