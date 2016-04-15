#include "bluetooththread.h"

bluetooththread::bluetooththread(QObject *parent) :
    QThread(parent)
{
    mBluetooth_setup = new bluetooth_setup();
    serial = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(serial, SIGNAL(readyRead()),this, SLOT(readyRead()));
    connect(serial, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(error(QBluetoothSocket::SocketError)));
    connect(serial, SIGNAL(connected()),this, SLOT(connected()));
    connect(serial, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(mBluetooth_setup, SIGNAL(PairDevicesNow()),this,SLOT(pairDeviceNow()));

}

void bluetooththread::showSetupWindow()
{
    mBluetooth_setup->show();
    disconnectDevice();
}


void bluetooththread::connectToSocketNow()
{
    if(mBluetooth_setup->hostStatus() == 0) //Bluetooth device turned off
    {
        mBluetooth_setup->turnBluetoothOn();
        QTimer::singleShot(3000, this ,SLOT(connectNow())); //Bluetooth Module need some time to init
    }
    else
    {
        QTimer::singleShot(1000, this, SLOT(connectNow()));
    }
}

void bluetooththread::pairDevice()
{
    BluetoothPairAddress = mBluetooth_setup->getAddress();
    BluetoothPairAddress.remove(":", Qt::CaseInsensitive);


    if(BluetoothPairAddress == "")
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Bluetooth Configuration",
                                                                       tr("There is no bluetooth address configured\n"
                                                                          "Would you like to search for one?"),
                                                                       QMessageBox::No | QMessageBox::Yes,
                                                                       QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes)
        {
            emit failedToConnect();
        }
        else
        {
            showSetupWindow();
        }

    }
    else
    {
        try
        {
            emit startConnecting();
            serial->connectToService(QBluetoothAddress(BluetoothPairAddress),QBluetoothUuid(QBluetoothUuid::SerialPort));

        }
        catch(...)
        {
             QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Bluetooth", "The Bluetooth device is not responding!\n"
                                                                                   "Please Try Connecting again");
             return;
        }


    }

}

void bluetooththread::unpairDevice()
{
    if(serial->UnconnectedState)
    {
        QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Bluetooth", "The Bluetooth is allready disconnected");
    }
    else
    {
      serial->disconnectFromService();
      emit failedToConnect();
    }

}

void bluetooththread::disconnectDevice()
{
    unpairDevice();
}

void bluetooththread::bluetoothPowerOn()
{
    mBluetooth_setup->turnBluetoothOn();
}


void bluetooththread::readyRead()
{
    QByteArray RxByteData;
    RxByteData = serial->readAll();

    emit readyRead(RxByteData);

}

void bluetooththread::error(QBluetoothSocket::SocketError error)
{

    switch (error) {
        case QBluetoothSocket::UnknownSocketError:
            emit failedToConnect();
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("Could not connect to the bluetooth\nCheck the bluetooth device"));
            break;
    case QBluetoothSocket::NoSocketError:
            emit failedToConnect();
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The host was not found. Please check that you are paired under setup"));            
            break;
        case QBluetoothSocket::HostNotFoundError:
            emit failedToConnect();
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The Bluetooth device was not found. "
                                        "Make sure you have choosen correct device, "
                                        "by checking that setup "
                                        "settings are correct."));
            break;
         case QBluetoothSocket::ServiceNotFoundError:
            emit failedToConnect();
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("The Bluetooth is not in range or turned off\nCheck the status on the Bluetooth unit!"));


            break;
    case QBluetoothSocket::OperationError:
            //QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"), tr("Lost the Bluetooth communication"));
            //emit failedToConnect();

            break;

        default:
            emit failedToConnect();
            QMessageBox::information(qobject_cast<QWidget *>(parent()), tr("Bluetooth Error"),
                                     tr("The following error occurred: %1.")
                                     .arg(serial->errorString()));

        break;

    }

}

void bluetooththread::connected()
{
    emit Doneconnecting();
}

void bluetooththread::disconnected()
{
    emit DoneDisconnecting();
}

void bluetooththread::connectNow()
{
    pairDevice();
}

QString bluetooththread::getBluetoothPairAddress() const
{
    return BluetoothPairAddress;
}

void bluetooththread::pairDeviceNow()
{
    pairDevice();
}

void bluetooththread::writeBytes(QByteArray array)
{
    serial->write(array, array.length());
}



