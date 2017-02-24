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
    QString CalculateCRC(const QString &string);
    bool CheckCRC(const QString &string);

    enum State {Start, Receiving, End};

    State state;
    QString rx;

signals:
    void freshData(QString string);
    void sendByteArrayToSocket(QByteArray array);

public slots:
    void Receive(QByteArray array);
    void Send(QString buffer);

private slots:


};

#endif // WDLINK_H
