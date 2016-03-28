#include "configureipportdialog.h"
#include "ui_configureipportdialog.h"

ConfigureIpPortDialog::ConfigureIpPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureIpPortDialog)
{
    ui->setupUi(this);

    ui->lineEditIpAdress->setInputMask("000.000.000.000");

    readSettings();

    qDebug() << getPort() << getIpAdress();

    ui->lineEditIpAdress->setText(getIpAdress());
    ui->lineEditPort->setText(QString::number(getPort()));
    ui->lineEditHttpAdress->setText(getHttpAdress());
    ui->lineEditCameraNumber->setText(QString::number(getWebCameraNumber()));

    setStreamType();
    setupApperance();

}

ConfigureIpPortDialog::~ConfigureIpPortDialog()
{
    delete ui;
}


void ConfigureIpPortDialog::on_pushButtonSaveAndClose_clicked()
{
   setPort(ui->lineEditPort->text().toUInt());
   setIpAdress(ui->lineEditIpAdress->text());
   setHttpAdress(ui->lineEditHttpAdress->text());
   setWebCameraNumber(ui->lineEditCameraNumber->text().toUInt());
   setStreamType();

   writeSettings();
   this->hide();

   qDebug() << ipAdress << port;
}

void ConfigureIpPortDialog::on_pushButtonCancel_clicked()
{
    this->hide();
}

void ConfigureIpPortDialog::writeSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_StreamCore");
    settings.setValue("ipAdress", ipAdress);
    settings.setValue("Port", port);
    settings.setValue("httpsAdress", httpAdress);
    settings.setValue("webCameraNumber", webCameraNumber);
    settings.setValue("radioButtonHttpStre", ui->radioButtonHttpStream->isChecked());
    settings.setValue("radioButtonIpStream", ui->radioButtonIpStream->isChecked());
    settings.setValue("radioButtonWebCamera", ui->radioButtonWebCamera->isChecked());
    settings.endGroup();
}

void ConfigureIpPortDialog::readSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_StreamCore");
    ipAdress = settings.value("ipAdress", ipAdress).toString();
    port = settings.value("Port", port).toUInt();
    httpAdress = settings.value("httpsAdress", httpAdress).toString();
    webCameraNumber = settings.value("webCameraNumber", webCameraNumber).toUInt();
    ui->radioButtonHttpStream->setChecked(settings.value("radioButtonHttpStre", ui->radioButtonHttpStream->isCheckable()).toBool());
    ui->radioButtonIpStream->setChecked(settings.value("radioButtonIpStream", ui->radioButtonIpStream->isCheckable()).toBool());
    ui->radioButtonWebCamera->setChecked(settings.value("radioButtonWebCamera", ui->radioButtonWebCamera->isCheckable()).toBool());
    settings.endGroup();
}

void ConfigureIpPortDialog::setupApperance()
{

}

void ConfigureIpPortDialog::setStreamType()
{
    if(ui->radioButtonHttpStream->isChecked())
    {
        typeStream = ui->radioButtonHttpStream->text();
    }
    else if(ui->radioButtonIpStream->isChecked())
    {
        typeStream = ui->radioButtonIpStream->text();
    }
    else if(ui->radioButtonWebCamera->isChecked())
    {
        typeStream = ui->radioButtonWebCamera->text();
    }



}

quint32 ConfigureIpPortDialog::getPort() const
{
    return port;
}

void ConfigureIpPortDialog::setPort(const quint32 &value)
{
    port = value;
}

QString ConfigureIpPortDialog::getIpAdress() const
{
    return ipAdress;
}

void ConfigureIpPortDialog::setIpAdress(const QString &value)
{
    ipAdress = value;
}


QString ConfigureIpPortDialog::getTypeStream() const
{
    return typeStream;
}

void ConfigureIpPortDialog::setTypeStream(const QString &value)
{
    typeStream = value;
}

quint16 ConfigureIpPortDialog::getWebCameraNumber() const
{
    return webCameraNumber;
}

void ConfigureIpPortDialog::setWebCameraNumber(const quint16 &value)
{
    webCameraNumber = value;
}

QString ConfigureIpPortDialog::getHttpAdress() const
{
    return httpAdress;
}

void ConfigureIpPortDialog::setHttpAdress(const QString &value)
{
    httpAdress = value;
}
