#include "tcpdialog.h"
#include "ui_tcpdialog.h"

TcpDialog::TcpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpDialog)
{
    ui->setupUi(this);
    ui->lineEditIpAdress->setInputMask("000.000.000.000");
    mTcpSocket = new QTcpSocket(this);
    IpAdress = new QHostAddress();
}

TcpDialog::~TcpDialog()
{
    delete ui;
}


void TcpDialog::on_pushButtonOk_clicked()
{

    requestCnodeData(120, 4, 'C' , mTcpSocket);
}

void TcpDialog::on_pushButtonCancel_clicked()
{
    this->hide();
}

void TcpDialog::on_checkBox_clicked()
{
    if(ui->lineEditIpAdress->isEnabled())
    {
        ui->lineEditIpAdress->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        ui->lineEditIpAdress->setText("10.10.100.254");
        ui->lineEditPort->setText("8899");
        port = ui->lineEditPort->text().toInt();
        IpAdress->setAddress(ui->lineEditIpAdress->text());
        mTcpSocket->connectToHost(*IpAdress,port);

        qDebug() << port << IpAdress;

    }
    else
    {
        ui->lineEditIpAdress->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
    }
}

void TcpDialog::requestCnodeData(qint8 messageID, qint8 op, char typeCmd, QTcpSocket *r_serial)
{
    QByteArray wakeUp;
    wakeUp.append((char)0xAA); // wake up command for c-node
    QByteArray sendData;
    QByteArray preamble;

    preamble.append("APC2UTB"); //Preamble
    sendData.append(0x02); //Length
    sendData.append((char)0x00); //length
    sendData.append((char)0x01); // Sequence number 0-255
    sendData.append(0x01); //address
    sendData.append(typeCmd); // Type command C = configuration T = test
    sendData.append(messageID); // MessageID
    sendData.append((op << 4)); // Operating parameter
    quint16 crc = CalculateCrc(sendData.constData(), sendData.length());

    sendData.append(crc); //First byte from calculateCrc
    sendData.append(crc >> 8); //Bitshifted crc to get the last byte

    preamble.append(sendData);

    if(r_serial->isOpen())
    {
    try
        {

       r_serial->write(wakeUp.data(), 1); //Sends wakeup 2 time which is 0xAA
       //this->msleep(500);
       r_serial->write(wakeUp.data(), 1);
       r_serial->write(preamble, preamble.length()); //Send kommando

       }
        catch(...)
        {


        }
        }
    else
    {
        QMessageBox::critical(qobject_cast<QWidget *>(parent()), "TCP Error", "Please check your connection");

    }
}
