#include "bluetoothserial.h"

BluetoothSerial::BluetoothSerial(QObject *parent) :
    QThread(parent)
{
    mBluetooth_setup = new bluetooth_setup();
    mBluetoothSerial =  new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);


    connect(mBluetoothSerial, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(mBluetooth_setup, SIGNAL(PairDevicesNow()), this, SLOT(connectToSocket()));
    connect(mBluetoothSerial, SIGNAL(connected()), this, SLOT(connected()));
    connect(mBluetoothSerial, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mBluetoothSerial, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(error(QBluetoothSocket::SocketError)));
}

BluetoothSerial::~BluetoothSerial()
{

}

void BluetoothSerial::writeBytes(QByteArray array)
{
    mBluetoothSerial->write(array, array.length());
  //  qDebug() << "Socket has sendt";
}

void BluetoothSerial::connectToSocket()
{
    connectDevice();

}

void BluetoothSerial::showSetupWindow()
{
    mBluetooth_setup->setModal(true);
    mBluetooth_setup->show();
}

void BluetoothSerial::bluetoothPowerOn()
{
    mBluetooth_setup->turnBluetoothOn();
}

void BluetoothSerial::connectDevice()
{
    BluetoothPairAddress = mBluetooth_setup->getAddress();
    BluetoothPairAddress.remove(":", Qt::CaseInsensitive);
    emit startConnecting();

    if(mBluetoothSerial->UnconnectedState)
    {

        QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Error", "The Bluetooth is not responding!\nTry again");

    }
    else
    {
        try
        {

            mBluetoothSerial->connectToService(QBluetoothAddress(BluetoothPairAddress),QBluetoothUuid(QBluetoothUuid::SerialPort));

        }
        catch(...)
        {
             QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Error", "The Bluetooth are not responding!\nTry again");
             return;
        }


    }

}

void BluetoothSerial::disconnectDevice()
{
    if(mBluetoothSerial->UnconnectedState)
    {
        //Not Connected
        return;
    }
    else
    {
        mBluetoothSerial->disconnectFromService();

    }

}

void BluetoothSerial::readyRead()
{
    QByteArray socketData;
    socketData = mBluetoothSerial->readAll();

    emit readyRead(socketData);

}

void BluetoothSerial::error(QBluetoothSocket::SocketError error)
{

    switch (error) {
        case QBluetoothSocket::UnknownSocketError:
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("Could not connect to the bluetooth\nCheck the bluetooth device"));
            emit failedToConnect();

            break;
    case QBluetoothSocket::NoSocketError:
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The host was not found. Please check that you are paired under setup"));
            emit failedToConnect();


            break;
        case QBluetoothSocket::HostNotFoundError:
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The Bluetooth device was not found. "
                                        "Make sure you have choosen correct device, "
                                        "by checking that setup "
                                        "settings are correct."));
            emit failedToConnect();

            break;
         case QBluetoothSocket::ServiceNotFoundError:
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The Bluetooth was not found\nCheck If The uTTC Is Turned On\nRun Setup and Scan for the devices"));
            emit failedToConnect();

            break;
    case QBluetoothSocket::OperationError:
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("Lost the Bluetooth communication"));
            emit failedToConnect();

            break;

        default:
           QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"),
                                     tr("The following error occurred: %1.")
                                     .arg(mBluetoothSerial->errorString()));
            emit failedToConnect();


    }

}

void BluetoothSerial::connected()
{
    emit Doneconnecting();

}

void BluetoothSerial::disconnected()
{
    emit disconnected();
}

void BluetoothSerial::startConnectingNow()
{

}

