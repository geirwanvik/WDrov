#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

#include "Communication/Serial/serial_setup.h"

class serialPort : public QObject
{
    Q_OBJECT
public:
    explicit serialPort(QObject *parent = 0);
    ~serialPort();
     void showSetupWindow();
     void connectToSocketNow();
     serial_setup *mSerialSetup;

     QString getPortName() const;
     void setPortName(const QString &value);

     qint32 getBaudRate() const;
     void setBaudRate(const qint32 &value);

signals:
     void readyRead(QByteArray Array);
     void serialWrite(QByteArray Array);
     void serialOpen(void);

public slots:
     void writeBytes(QByteArray array);
     void connectToSocket(void);


private slots:
    void readyRead(void);
    void error(QSerialPort::SerialPortError error);


private:
    QSerialPort *serial;
    QString portName;
    qint32 baudRate;
    void connectToPort(void);
    void disconnect(void);

};

#endif // SERIALPORT_H
