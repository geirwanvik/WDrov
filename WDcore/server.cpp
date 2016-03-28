#include "server.h"

#include <QDebug>

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
    socket = new QTcpSocket(this);

    connect (socket, SIGNAL(connected()), this, SLOT(connected()));
    connect (socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect (socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Server::StartServer()
{
    if (listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server started";
    }
    else
    {
        qDebug() << "Server failed";
    }

}

void Server::connected()
{
    qDebug() << "Client connected";
}

void Server::disconnected()
{
    qDebug() << "Client disconnected";
}

void Server::incomingConnection(int handle)
{
    if (socket->setSocketDescriptor(handle))
    {
        qDebug() << "Connection accepted";
    }
    else
    {
        qDebug() << "Connection failed";
    }
}

void Server::readyRead()
{
    QString input = socket->readAll();
    emit NewDataReceived(input);
}

void Server::transmitt(QString &string)
{
    QByteArray transmittArray = string.toLatin1();
    socket->write(transmittArray);
}




