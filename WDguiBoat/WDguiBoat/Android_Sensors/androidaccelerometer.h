#ifndef ANDROIDACCELEROMETER_H
#define ANDROIDACCELEROMETER_H

#include <QObject>
#include <QDebug>
#include <QAccelerometer>
#include <QAccelerometerReading>

class androidAccelerometer : public QObject
{
    Q_OBJECT
public:
    explicit androidAccelerometer(QObject *parent = 0);

signals:

public slots:

private:
     QAccelerometer *accmeter;
     QAccelerometerReading *reading;

     qreal x;
     qreal y;
     qreal z;

private slots:
     void readyReadSensor();

};

#endif // ANDROIDACCELEROMETER_H
