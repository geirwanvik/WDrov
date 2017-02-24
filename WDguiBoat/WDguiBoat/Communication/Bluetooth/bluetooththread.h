#ifndef BLUETOOTHTHREAD_H
#define BLUETOOTHTHREAD_H

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
#include <QTimer>




QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)
QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)


#include "Communication/Bluetooth/bluetooth_setup.h"

class bluetooththread : public QThread
{
    Q_OBJECT
public:
    explicit bluetooththread(QObject *parent = 0);
    bluetooth_setup *mBluetooth_setup;
    void showSetupWindow();
    QBluetoothSocket *serial;

    //Call this for connecting
    void connectToSocketNow(void);
    void disconnectDevice();
    void bluetoothPowerOn(void);

    QString getBluetoothPairAddress() const;

signals:
    void readyRead(QByteArray Array);
    //Signal emited for status of bluetooth socket
    void startConnecting();
    void Doneconnecting();
    void DoneDisconnecting();
    void failedToConnect();

public slots:
    //Slot for connecting
    void pairDeviceNow(void);
    //Signal for writing bytes with bluetooth socket
    void writeBytes(QByteArray array);
    void writeString(QString &String);

private slots:
    void readyRead();
    void error(QBluetoothSocket::SocketError error);
    void connected();
    void disconnected();
    void connectNow();

private:
    QString BluetoothPairAddress;
     void pairDevice();
     void unpairDevice();
     void showFailedToConnectMessage();
};

#endif // BLUETOOTHTHREAD_H
