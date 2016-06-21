#include "lightsensor.h"

lightSensor::lightSensor(QObject *parent) : QObject(parent)
{

    mLightSensor = new QLightSensor(this);
    mLightSensor->start();



    mAmbientSensor = new QAmbientLightSensor(this);
    connect(mAmbientSensor, SIGNAL(readingChanged()), this, SLOT(ReadAmbientSensor()));
    mAmbientSensor->start();


}

void lightSensor::ReadLightSensor()
{

}

void lightSensor::ReadAmbientSensor()
{
    qDebug() << "READING AMBIENT SENSOR: " << mAmbientSensor->reading()->Light;
}
