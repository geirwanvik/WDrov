#include <QCoreApplication>
#include <QThread>
#include <QMutex>
#include "server.h"
#include "imu.h"
#include "WDlink.h"
#include "motor.h"
#include <unistd.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMutex i2cMutex;
    QThread imuThread;

    WDlink wdLink;

    Imu imu(imuThread,i2cMutex);
    imu.moveToThread(&imuThread);
    imuThread.start();

    Motor motor(i2cMutex);

    Server server;
    server.StartServer();

    QObject::connect(&server,SIGNAL(NewDataReceived(QString&)), &wdLink, SLOT(NewMessage(QString&)));
    QObject::connect(&wdLink, SIGNAL(SendMessage(QString&)), &server, SLOT(transmitt(QString&)));

    QObject::connect(&wdLink, SIGNAL(GetMessageItem(QString,QString)), &imu, SLOT(NewMessageItem(QString,QString)), Qt::DirectConnection);
    QObject::connect(&imu, SIGNAL(SendReply(QString,QString)), &wdLink, SLOT(AddToReply(QString,QString)));

    QObject::connect(&wdLink, SIGNAL(GetMessageItem(QString,QString)), &motor, SLOT(NewMessageItem(QString,QString)));
    QObject::connect(&motor, SIGNAL(SendReply(QString,QString)), &wdLink, SLOT(AddToReply(QString,QString)));

    return a.exec();
}
