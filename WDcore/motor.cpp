#include "motor.h"

Motor::Motor(QMutex &_i2cMutex) :
    QObject(0)
{
    i2cMutex = &_i2cMutex;
}

void Motor::NewMessageItem(QString cmd, QString value)
{
    if (value == "READ")
    {
        int data;
        if (cmd == "MOTOR1")
        {
            data = pwm.getPWM(1);
            emit SendReply(cmd, QString::number(data));
        }
        if (cmd == "MOTOR2")
        {
            data = pwm.getPWM(2);
            emit SendReply(cmd, QString::number(data));
        }
        if (cmd == "MOTOR3")
        {
            data = pwm.getPWM(3);
            emit SendReply(cmd, QString::number(data));
        }
        if (cmd == "MOTOR4")
        {
            data = pwm.getPWM(4);
            emit SendReply(cmd, QString::number(data));
        }
    }
    else
    {
        bool ok;
        int data = value.toInt(&ok,10);
        if (!ok)
        {
            return;
        }

        if (cmd == "MOTOR1")
        {
            pwm.setPWM(1,data);
        }
        if (cmd == "MOTOR2")
        {
            pwm.setPWM(2,data);
        }
        if (cmd == "MOTOR3")
        {
            pwm.setPWM(3,data);
        }
        if (cmd == "MOTOR4")
        {
            pwm.setPWM(4,data);
        }
    }
}


