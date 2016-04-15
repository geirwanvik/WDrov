#include "serialport.h"

serialPort::serialPort(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
    QSerialPort::connect(serial, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));

    mSerialSetup = new serial_setup();
    connect(mSerialSetup, SIGNAL(connectToPort()),this, SLOT(connectToSocket()));

}

serialPort::~serialPort()
{

}

void serialPort::showSetupWindow()
{
    serial->close();
    mSerialSetup->setModal(true);
    mSerialSetup->GetPortInfo();
    mSerialSetup->show();
}

void serialPort::connectToSocketNow()
{
    portName = mSerialSetup->getPort();
    baudRate = mSerialSetup->getBaud();

    if(portName == "")
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Communication Setup",
                                                                    tr("No Serial Port Is Configured!\n"
                                                                       "Would You Like To Configure A Port?").arg(portName),
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);

        if (resBtn != QMessageBox::Yes)
        {
           return;
        }
        else
        {
           serial->close();
           mSerialSetup->setModal(true);
           mSerialSetup->show();
        }

    }
    else
    {
       QTimer::singleShot(2000, this, SLOT(connectToSocket()));
    }
}

void serialPort::writeBytes(QByteArray array)
{
    serial->write(array, array.length());
    emit serialWrite(array);
}

void serialPort::connectToSocket()
{
    connectToPort();
}


void serialPort::readyRead()
{
    QByteArray socketData;
    socketData = serial->readAll();

    emit readyRead(socketData);

}

void serialPort::error(QSerialPort::SerialPortError error)
{

    switch (error) {
    case QSerialPort::NoError:
        qDebug() << "No Error";
        break;
    case QSerialPort::DeviceNotFoundError:
        qDebug() << "Device not found Error";
        break;
    case QSerialPort::PermissionError:
        qDebug() << "Permission Error";
        break;
    case QSerialPort::OpenError:
        qDebug() << "Open Error";
        break;
    case QSerialPort::NotOpenError:
        qDebug() << "Not Open Error";
        break;
    case QSerialPort::ParityError:
        qDebug() << "Parity Error";
        break;
    case QSerialPort::FramingError:
        qDebug() << "Framing Error";
        break;
    case QSerialPort::BreakConditionError:
        qDebug() << "Break condition Error";
        break;
    case QSerialPort::WriteError:
        qDebug() << "Write Error";
        break;
    case QSerialPort::ReadError:
        qDebug() << "Read Error";
        break;
    case QSerialPort::ResourceError:
        qDebug() << "Resource Error";
        break;
    case QSerialPort::UnsupportedOperationError:
        qDebug() << "Unsupported Operation Error";
        break;
    case QSerialPort::TimeoutError:
        qDebug() << "Timeout Error";
        break;
    case QSerialPort::UnknownError:
        qDebug() << "Unknown Error";
        break;
    default:
        break;
    }

}

qint32 serialPort::getBaudRate() const
{
    return baudRate;
}

void serialPort::setBaudRate(const qint32 &value)
{
    baudRate = value;
}

QString serialPort::getPortName() const
{
    return portName;
}

void serialPort::setPortName(const QString &value)
{
    portName = value;
}

void serialPort::connectToPort()
{

    portName = mSerialSetup->getPort();
    baudRate = mSerialSetup->getBaud();
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);


    if(serial->isOpen())
    {
        QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Serial Port Error", "The Port Is Allready Open!");
    }
    else
    {
        serial->open(QIODevice::ReadWrite);

        if(serial->isOpen())
        {
            emit serialOpen();
        }
        else
        {
             QMessageBox::StandardButton resBtn = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Communication Setup",
                                                                         tr("Cant connect to serial port %1!\n"
                                                                            "Would You Like To Open Setup Window?").arg(portName),
                                                                         QMessageBox::No | QMessageBox::Yes | QMessageBox::Retry,
                                                                         QMessageBox::Retry);

             if (resBtn == QMessageBox::Yes || resBtn == QMessageBox::Retry)
             {
                if(resBtn == QMessageBox::Retry)
                {
                    connectToSocket();
                }
                else
                {
                    serial->close();
                    mSerialSetup->setModal(true);
                    mSerialSetup->show();
                }
             }
             else
             {
               return;
             }

        }
    }


}

void serialPort::disconnect()
{
    if(serial->isOpen())
    {
        serial->close();
    }
    else
    {
        QMessageBox::critical(qobject_cast<QWidget *>(parent()), "Serial Port Error", "The Port Is Allready Closed!");
    }

}

