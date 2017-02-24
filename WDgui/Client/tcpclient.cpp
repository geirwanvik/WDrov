#include "tcpclient.h"

tcpClient::tcpClient(QObject *parent) : QObject(parent)
{
    mClientSetupDialog = new clientSetupDialog();

   // mSocket = new QTcpSocket(this);
  //  connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
   // connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyReadString()));
   // connect(mSocket, SIGNAL(connected()), this, SLOT(connectedToHost()));
  //  connect(mSocket, SIGNAL(disconnected()),this, SLOT(connectedToHost()));
  //  connect(mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

 //   QTimer::singleShot(1000, this, SLOT(connectToHost())); // Give the rest of the object time to init!

}

void tcpClient::showClientSetupDialog()
{
    mClientSetupDialog->setModal(true);
    mClientSetupDialog->show();
}

void tcpClient::writeBytes(QByteArray Array)
{
 //   qDebug() << "TCP CLient send:" << Array;
    mSocket->write(Array);
}

void tcpClient::writeString(QString &String)
{
  //  qDebug() << "Client Send: " << String;
    String += '\n';
    QByteArray array(String.toStdString().c_str(), String.length());

    mSocket->write(array, array.length());

    array.clear();
}

void tcpClient::connectToHost()
{
    hostAdress = mClientSetupDialog->getIpAdress();
    hostPort = mClientSetupDialog->getPort();

    qDebug() << "Connected To Server: " << hostAdress << hostPort;

    mSocket->connectToHost(hostAdress, hostPort, QIODevice::ReadWrite);
    mSocket->waitForConnected(5000);
}



void tcpClient::readyRead()
{
    //QByteArray temp;
    //temp = mSocket->readAll();
    //emit incommingData(temp);


}

void tcpClient::readyReadString()
{
     QString input = mSocket->readAll();
     emit newDataRx(input);
    // qDebug() <<input;
}

void tcpClient::connectedToHost()
{
    if(mSocket->isOpen())
    {
        emit clientConnected(true);
        qDebug() << "We are connected!";
    }
    else
    {
        emit clientConnected(false);
    }
}

void tcpClient::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << "We have a error!" << socketError;
}
