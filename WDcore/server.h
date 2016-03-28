#ifndef SERVER_H
#define SERVER_H
#include "WDlink.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    void StartServer();

protected:
    void incomingConnection(int handle);

signals:
    void NewDataReceived(QString &string);
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void transmitt(QString &string);

private:
    QTcpSocket *socket;

};

#endif // SERVER_H
