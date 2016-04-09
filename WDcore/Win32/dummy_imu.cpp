#include "imu.h"
#include "imuhelperfunctions.h"
#include "wiringPi.h"
#include <unistd.h>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>
#include <qmath.h>

Imu::Imu(QThread &thread, QMutex &_i2cMutex) :
    QObject(0)
{
    (void)_i2cMutex;
    memset(&att,0,sizeof(att_t));
    connect (&thread, SIGNAL(started()), this, SLOT(Calculate()));
}

void Imu::Calculate()
{
    int mode = qrand() % 3;
    int tilt = qrand() % 900;
    int head = qrand() % 1800;
    int sign = qrand() % 2;
    if (sign == 1)
    {
        tilt *= -1;
        head *= -1;
    }

    while (1)
    {
        switch (mode)
        {
        case 0: // pitch
            if (att.angle[PITCH] == tilt)
            {
                mode = qrand() % 3;
                tilt = qrand() % 900;
                head = qrand() % 1800;
                sign = qrand() % 2;
                if (sign == 1)
                {
                    tilt *= -1;
                    head *= -1;
                }
            }
            else
            {
                if (att.angle[PITCH] < tilt)
                {
                    att.angle[PITCH]++;
                }
                else
                {
                    att.angle[PITCH]--;
                }
            }
            break;
        case 1: // roll
            if (att.angle[ROLL] == tilt)
            {
                mode = qrand() % 3;
                tilt = qrand() % 900;
                head = qrand() % 1800;
                sign = qrand() % 2;
                if (sign == 1)
                {
                    tilt *= -1;
                    head *= -1;
                }
            }
            else
            {
                if (att.angle[ROLL] < tilt)
                {
                    att.angle[ROLL]++;
                }
                else
                {
                    att.angle[ROLL]--;
                }
            }
            break;
        case 2: // head
            if (att.heading == head)
            {
                mode = qrand() % 3;
                tilt = qrand() % 900;
                head = qrand() % 1800;
                sign = qrand() % 2;
                if (sign == 1)
                {
                    tilt *= -1;
                    head *= -1;
                }
            }
            else
            {
                if (att.heading < head)
                {
                    att.heading++;
                }
                else
                {
                    att.heading--;
                }
            }
            break;
        }
        qDebug() << "Roll: " << QString::number(att.angle[ROLL]) << " Pitch: " << QString::number(att.angle[PITCH]) << " Heading: " << QString::number(att.heading);
        QMutex mutex;
        mutex.lock();

        QWaitCondition waitCondition;
        waitCondition.wait(&mutex, 5);

        mutex.unlock();
    }
}

void Imu::NewMessageItem(QString cmd, QString value)
{
    float data;
    if (value == "READ")
    {
        if (cmd == "ROLL")
        {
            data = (float)att.angle[ROLL] / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
        else if (cmd == "PITCH")
        {
            data = (float)att.angle[PITCH] / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
        else if (cmd == "HEADING")
        {
            data = (float)att.heading / 10;
            emit SendReply(cmd, QString::number(data,'f',1));
        }
    }
}
