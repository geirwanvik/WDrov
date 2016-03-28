#include "pca9685.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PCA9685_ADDRESS 0x40

#define MODE1 0x00			//Mode  register  1
#define MODE2 0x01			//Mode  register  2
#define SUBADR1 0x02		//I2C-bus subaddress 1
#define SUBADR2 0x03		//I2C-bus subaddress 2
#define SUBADR3 0x04		//I2C-bus subaddress 3
#define ALLCALLADR 0x05     //LED All Call I2C-bus address
#define LED0 0x6			//LED0 start register
#define LED0_ON_L 0x6		//LED0 output and brightness control byte 0
#define LED0_ON_H 0x7		//LED0 output and brightness control byte 1
#define LED0_OFF_L 0x8		//LED0 output and brightness control byte 2
#define LED0_OFF_H 0x9		//LED0 output and brightness control byte 3
#define LED_MULTIPLYER 4	// For the other 15 channels
#define ALLLED_ON_L 0xFA    //load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALLLED_ON_H 0xFB	//load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALLLED_OFF_L 0xFC	//load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALLLED_OFF_H 0xFD	//load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 0xFE		//prescaler for output frequency
#define CLOCK_FREQ 25000000.0 //25MHz default osc clock

int PCA_FD;

Pca9685::Pca9685()
{
    PCA_FD = wiringPiI2CSetup(PCA9685_ADDRESS);
    reset();
    setPWMFreq(450);
}

void Pca9685::setPWMFreq(int freq)
{
    uint8_t prescale_val = (CLOCK_FREQ / (4096 * freq))  - 1;
    wiringPiI2CWriteReg8(PCA_FD, MODE1, 0x10); //sleep

    wiringPiI2CWriteReg8(PCA_FD, PRE_SCALE, prescale_val); // multiplyer for PWM frequency
    wiringPiI2CWriteReg8(PCA_FD, MODE1, 0x80); //restart
    wiringPiI2CWriteReg8(PCA_FD, MODE2, 0x04); //totem pole (default)
}

void Pca9685::setPWM(uint8_t led, int on_value, int off_value)
{
    wiringPiI2CWriteReg8(PCA_FD, LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF);
    wiringPiI2CWriteReg8(PCA_FD, LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8);
    wiringPiI2CWriteReg8(PCA_FD, LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF);
    wiringPiI2CWriteReg8(PCA_FD, LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8);

}

void Pca9685::setPWM(uint8_t led, int value)
{
    setPWM(led, 0, value);
}

int Pca9685::getPWM(uint8_t led)
{
    int ledval = 0;
    ledval = wiringPiI2CReadReg8(PCA_FD, LED0_OFF_H + LED_MULTIPLYER * (led-1));
    ledval = ledval & 0xf;
    ledval <<= 8;
    ledval += wiringPiI2CReadReg8(PCA_FD, LED0_OFF_L + LED_MULTIPLYER * (led-1));
    return ledval;
}

void Pca9685::reset()
{
    wiringPiI2CWriteReg8(PCA_FD, MODE1, 0x00); //Normal mode
    wiringPiI2CWriteReg8(PCA_FD, MODE2, 0x04); //totem pole
}
