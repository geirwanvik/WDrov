#include "allsensorsdialog.h"
#include "ui_allsensorsdialog.h"

AllSensorsDialog::AllSensorsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllSensorsDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else

#endif
}

AllSensorsDialog::~AllSensorsDialog()
{
    delete ui;
}

void AllSensorsDialog::sensorData(QStringList StringList)
{
    if(StringList.contains("GPS_LAT") || StringList.contains("GPS_LON"))
    {
        //qDebug() << StringList[6] << StringList[7] << StringList[8] << StringList[9];
       ui->labelGpsLat->setText(StringList[0] + " : " + StringList[1]);
       ui->labelGpsLon->setText(StringList[2] + " : " + StringList[3]);
       ui->labelGpsAlt->setText(StringList[4] + " : " + StringList[5]);
       ui->labelGpsGroundSpeed->setText(StringList[6] + " : " + StringList[7]);
       ui->labelGps3DSpeed->setText(StringList[8] + " : " + StringList[9]);
       ui->labelGpsGroundCourse->setText(StringList[10] + " : " + StringList[11]);
       ui->labelGpsNumberSats->setText(StringList[12] + " : " + StringList[13]);
       ui->labelGpsFix->setText(StringList[14] + " : " + StringList[15]);

    }
    else if(StringList.contains("IMU_ROLL") || StringList.contains("IMU_PITCH"))
    {
       // qDebug() << StringList[0] << StringList[1] << StringList[2] << StringList[3];
        ui->labelRoll->setText(StringList[0] + " : " + StringList[1]);
        ui->labelPitch->setText(StringList[2] + " : " + StringList[3]);
        ui->labelHeading->setText(StringList[4] + " : " + StringList[5]);

    }
    else if(StringList.contains("DHT22_TEMP") || StringList.contains("DHT22_HUM"))
    {
       qDebug() << StringList[0] << StringList[1] << StringList[2] << StringList[3];
        ui->labelDhtTemp->setText(StringList[0] + " : " + StringList[1]);
        ui->labelDhtHumidity->setText(StringList[2] + " : " + StringList[3]);
    }
    else if(StringList.contains("VOLTAGE") || StringList.contains("CURRENT"))
    {
        ui->labelVoltage12v->setText(StringList[0] + " : " + StringList[1]);
        ui->labelSystemCurrent->setText(StringList[2] + " : " + StringList[3]);
    }
    else
    {
        return;
    }
}

void AllSensorsDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}
