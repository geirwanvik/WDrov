#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <QObject>
#include <QLightSensor>
#include <QLightReading>
#include <QAmbientLightSensor>
#include <QAmbientLightReading>
#include <QDebug>

class lightSensor : public QObject
{
    Q_OBJECT
public:
    explicit lightSensor(QObject *parent = 0);
    QLightSensor *mLightSensor;
    QAmbientLightSensor *mAmbientSensor;

signals:

public slots:

private:


private slots:
    void ReadLightSensor();
    void ReadAmbientSensor();
};

#endif // LIGHTSENSOR_H
