#include "pca9685.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

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
