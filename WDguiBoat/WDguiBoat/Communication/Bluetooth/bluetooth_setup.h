#ifndef BLUETOOTH_SETUP_H
#define BLUETOOTH_SETUP_H

#include <QDialog>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <QMenu>
#include <QDebug>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothaddress.h>
#include <QRect>
#include <QDesktopWidget>
#include <QMap>
#include <QSettings>
#include <QScroller>
#include <QToolBar>
#include <QLabel>
#include <QThread>



QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)
QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

typedef struct BLUETOOTH_INFO_ADDRESS
{
   QString Name;
   QString Address;

}BLUETOOTH_INFO;


namespace Ui {
class bluetooth_setup;
}

class bluetooth_setup : public QDialog
{
    Q_OBJECT

public:
    explicit bluetooth_setup(QWidget *parent = 0);
    ~bluetooth_setup();
    QString getAddress();
    int hostStatus();
    void turnBluetoothOn(void);
    QString getBluetoothAddress() const;
    void setBluetoothAddress(const QString &value);

private slots:
    void on_pushButtonScan_clicked();
    void on_pushButtonCancel_clicked();
    void addDevice(const QBluetoothDeviceInfo&);
    void scanFinished();
    void stopScanning();
    void on_pushButtonOk_clicked();

private:
    Ui::bluetooth_setup *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    void updateAddress(void);
    QString BluetoothAddress;
    QBluetoothLocalDevice localdevice;
    BLUETOOTH_INFO BluetoothInfo;
    QMap<QString, QString> bluetoothDevices;
    void WriteSettings(void);
    void ReadSettings(void);



     QToolBar *ToolBar;
     QLabel *LabelToolBar;
     void createToolBar(void);

signals:
    void PairDevicesNow(void);


};

#endif // BLUETOOTH_SETUP_H
