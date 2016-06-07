#pragma once
#include "Arduino.h"

class _I2cHelper
{
public:
	 void init(void);
	 void read(uint8_t address, uint8_t reg, void *buf, uint8_t size);
	 void write(uint8_t address, uint8_t reg, uint8_t val);
private:
	 void i2c_rep_start(uint8_t address);
	 void i2c_write(uint8_t data);
	 void i2c_read_to_buf(uint8_t add, void *buf, uint8_t size);
	 void i2c_stop(void);
	 void waitTransmissionI2C(void);
	 uint8_t i2c_read(uint8_t ack);
};
extern _I2cHelper I2cHelper;

