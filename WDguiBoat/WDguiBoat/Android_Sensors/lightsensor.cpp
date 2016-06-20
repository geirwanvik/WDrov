#include "lightsensor.h"

lightSensor::lightSensor(QObject *parent) : QObject(parent)
{

    mLightSensor = new QLightSensor(this);
    connect(mLightSensor, SIGNAL(readingChanged()), this, SLOT(ReadLightSensor()));
    mLightSensor->start();



    mAmbientSensor = new QAmbientLightSensor(this);
    connect(mAmbientSensor, SIGNAL(readingChanged()), this, SLOT(ReadAmbientSensor()));
    mAmbientSensor->start();


}

void lightSensor::ReadLightSensor()
{
    qDebug() << "READING LIGHT SENSOR:" << mLightSensor->reading()->lux();
}

void lightSensor::ReadAmbientSensor()
{
    qDebug() << "READING AMBIENT SENSOR: " << mAmbientSensor->reading()->Light;
}
