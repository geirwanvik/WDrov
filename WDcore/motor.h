#ifndef MOTOR_H
#define MOTOR_H

#include <QObject>
#include <QMutex>

#include "pca9685.h"

class Motor : public QObject
{
    Q_OBJECT
public:
    explicit Motor(QMutex &_i2cMutex);
    void RegisterMutex();

signals:
    void SendReply(QString cmd, QString value);

public slots:
    void NewMessageItem(QString cmd, QString value);

private:
    Pca9685 pwm;
    QMutex *i2cMutex;

};

#endif // MOTOR_H
