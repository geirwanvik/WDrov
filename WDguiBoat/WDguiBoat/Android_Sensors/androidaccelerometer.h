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
    QAccelerometer *accmeter;

signals:

public slots:

private:
     qreal x;
     qreal y;
     qreal z;

private slots:
     void readyReadSensor();

};

#endif // ANDROIDACCELEROMETER_H
