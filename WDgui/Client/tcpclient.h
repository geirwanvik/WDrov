#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

#include "Client/clientsetupdialog.h"

class tcpClient : public QObject
{
    Q_OBJECT
public:
    explicit tcpClient(QObject *parent = 0);
    void showClientSetupDialog();
    QTcpSocket *mSocket;

signals:
    void incommingData(QByteArray Array);
    void newDataRx(QString &String);
    void clientConnected(bool Status);

public slots:
      void writeBytes(QByteArray Array);
      void writeString(QString &String);
      void connectToHost();

private:
    clientSetupDialog *mClientSetupDialog;

    QString hostAdress;
    quint32 hostPort;


private slots:
     void readyRead();
     void readyReadString();
     void connectedToHost();

     void error(QAbstractSocket::SocketError socketError);


};

#endif // TCPCLIENT_H
