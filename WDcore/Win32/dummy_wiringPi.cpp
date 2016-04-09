#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "imuhelperfunctions.h"
#include "pca9685.h"

#include <QElapsedTimer>

QElapsedTimer timer;

void delay(unsigned int howLong)
{
    if (!timer.isValid())
        timer.start();
    quint64 now = howLong + timer.elapsed();

    while ( now > timer.elapsed())
    {}
}

void delayMicroseconds(unsigned int howLong)
{
    if (!timer.isValid())
        timer.start();
    quint64 now = howLong + timer.nsecsElapsed();

    while ( now > timer.nsecsElapsed())
    {}
}

unsigned int millis(void)
{
    if (!timer.isValid())
        timer.start();
    return (unsigned int)timer.elapsed();
}

unsigned int micros(void)
{
    if (!timer.isValid())
        timer.start();
    return (unsigned int)(timer.nsecsElapsed() / 1000);
}

int wiringPiI2CReadReg8(int fd, int reg)
{
    (void)fd;
    (void)reg;
    return 1;
}


int wiringPiI2CWriteReg8(int fd, int reg, int data)
{
    (void)fd;
    (void)data;
    (void)reg;
    return 1;
}

int wiringPiI2CSetup(const int devId)
{
    return 1;
}
