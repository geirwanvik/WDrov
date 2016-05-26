#include "androidaccelerometer.h"

androidAccelerometer::androidAccelerometer(QObject *parent) : QObject(parent)
{
    accmeter = new QAccelerometer(this);
    connect(accmeter, SIGNAL(readingChanged()), this, SLOT(readyReadSensor()));
    accmeter->startTimer(1000);
    accmeter->start();

}

void androidAccelerometer::readyReadSensor()
{
    x = accmeter->reading()->x();
    y = accmeter->reading()->y();
    qDebug() << x << y;
}
