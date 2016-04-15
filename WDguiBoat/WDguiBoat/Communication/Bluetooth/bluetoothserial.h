#ifndef BLUETOOTHSERIAL_H
#define BLUETOOTHSERIAL_H

#include <QObject>
#include <QThread>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <QMenu>
#include <QDebug>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothaddress.h>
#include <QBluetoothSocket>
#include <QMessageBox>

#include "Communication/Bluetooth/bluetooth_setup.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)
QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

class BluetoothSerial : public QThread
{
    Q_OBJECT
public:
    explicit BluetoothSerial(QObject *parent = 0);
    ~BluetoothSerial();
    void showSetupWindow();
    void bluetoothPowerOn(void);
    void connectDevice(void);

signals:
    void readyRead(QByteArray Array);
    void startConnecting(void);
    void Doneconnecting(void);
    void DoneDisconnecting(void);
    void failedToConnect(void);

private:
    bluetooth_setup *mBluetooth_setup;
    QBluetoothSocket *mBluetoothSerial;
    QString BluetoothPairAddress;    


public slots:
    void writeBytes(QByteArray array);
    void connectToSocket(void);
    void disconnectDevice(void);

private slots:
    void readyRead(void);
    void error(QBluetoothSocket::SocketError error);
    void connected(void);
    void disconnected(void);
    void startConnectingNow(void);

};

#endif // BLUETOOTHSERIAL_H
