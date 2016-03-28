#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void SetSocket(int descriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *socket;

};

#endif // CLIENT_H
