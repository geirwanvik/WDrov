#include "androidcompass.h"

androidCompass::androidCompass(QObject *parent) : QObject(parent)
{
    mCompass = new QCompass(this);
    mCompass->start();
}

