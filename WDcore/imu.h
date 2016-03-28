#ifndef IMU_H
#define IMU_H

#include <QObject>
#include <QThread>
#include <QMutex>

#include "mpu6050.h"

class Imu : public QObject
{
    Q_OBJECT
public:
    explicit Imu(QThread &thread, QMutex &_i2cMutex);

signals:
    void SendReply(QString cmd, QString value);

public slots:
    void Calculate();
    void NewMessageItem(QString cmd, QString value);

private:
    void GetEstimatedAttitude();
    Mpu6050 mpu;
    QMutex *i2cMutex;

};

#endif // IMU_H
