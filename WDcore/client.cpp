#include "client.h"
#include <QDebug>
#include <QStringList>
Client::Client(QObject *parent) :
    QObject(parent)
{
}

void Client::SetSocket(int descriptor)
{
    socket = new QTcpSocket(this);

    connect (socket, SIGNAL(connected()), this, SLOT(connected()));
    connect (socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect (socket,SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);
}

void Client::connected()
{
    qDebug() << "Client connected";
}

void Client::disconnected()
{
    qDebug() << "Client disconnected";
}

void Client::readyRead()
{
    bool ok;
    QString input = socket->readAll();
    input = input.trimmed();

    int index = input.lastIndexOf('*');
    QString crcChars = input.mid(index +1);
    int crcDec = crcChars.toUInt(&ok, 16);
    if (!ok)
    {
        return;
    }

    QStringList parsedList = input.split(',');

    foreach (QString item, parsedList)
    {
        qDebug() << item;
    }
    qDebug() << "And the CRC was " << QString::number(crcDec);

}
