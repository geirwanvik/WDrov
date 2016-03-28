#include "clientsetupdialog.h"
#include "ui_clientsetupdialog.h"

clientSetupDialog::clientSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientSetupDialog)
{
    ui->setupUi(this);

    ui->lineEditIpAdress->setInputMask("000.000.000.000");

    readSettings();

    qDebug() << "Server Connection: " << ipAdress << port;

    ui->lineEditIpAdress->setText(getIpAdress());
    ui->lineEditPort->setText(QString::number(getPort()));


}

clientSetupDialog::~clientSetupDialog()
{
    delete ui;
}

QString clientSetupDialog::getIpAdress() const
{
    return ipAdress;
}

void clientSetupDialog::setIpAdress(const QString &value)
{
    ipAdress = value;
}

quint32 clientSetupDialog::getPort() const
{
    return port;
}

void clientSetupDialog::setPort(const quint32 &value)
{
    port = value;
}

void clientSetupDialog::writeSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_TcpClient");
    settings.setValue("ipAdressServer", ipAdress);
    settings.setValue("PortServer", port);
    settings.endGroup();
}

void clientSetupDialog::readSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_TcpClient");
    ipAdress = settings.value("ipAdressServer", ipAdress).toString();
    port = settings.value("PortServer", port).toUInt();
    settings.endGroup();
}

void clientSetupDialog::on_pushButtonSaveClose_clicked()
{
    ipAdress = ui->lineEditIpAdress->text();
    port = ui->lineEditPort->text().toUInt();
    writeSettings();
    this->hide();

}

void clientSetupDialog::on_pushButtonCancel_clicked()
{
    this->hide();
}
