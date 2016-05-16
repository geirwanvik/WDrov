#ifndef WDLINK_H
#define WDLINK_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTimer>


class WDLink : public QObject
{
    Q_OBJECT
public:
    explicit WDLink(QObject *parent = 0);
    void Receive(unsigned char data);
    void Send(QString *buffer);


private:
    unsigned char CalculateCRC(const char *buffer);
    unsigned char CheckCRC(const char *buffer);
    enum State {Start, Receiving, End};

    State state;
    QString rx;
    QString tx;



    QByteArray reSendData;




signals:
    void freshData(QString string);
    void freshSendData(QString string);
    void sendByteArrayToSocket(QByteArray Array);

public slots:
    void ReveiveSlot(unsigned char data);
    void inncommingData(QByteArray Array);
    void sendFreshSocketData(QString string);
    void sendData(QString buffer);

private slots:


};

#endif // WDLINK_H
