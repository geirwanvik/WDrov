#include "androidcompass.h"

androidCompass::androidCompass(QObject *parent) : QObject(parent)
{
    mCompass = new QCompass(this);


    connect(mCompass, SIGNAL(readingChanged()),this, SLOT(readyReadSensor()));
}

void androidCompass::readyReadSensor()
{
    //qDebug() << mCompass->reading()->calibrationLevel();
}
