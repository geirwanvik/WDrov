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
    this->resize(1000,750);
#endif


     QScroller *scroller = QScroller::scroller(ui->scrollArea);
     scroller->grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);
}

AllSensorsDialog::~AllSensorsDialog()
{
    delete ui;
}

void AllSensorsDialog::sensorData(QString command, QString value)
{
    ushort i = 0;
    for (;i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
    {
        if (command == CommandString[i])
        {
            break;
        }
    }

    switch (i) {
    case GPS_LAT:
        ui->labelGpsLat->setText(command + " " + value);
        break;
    case GPS_LON:
        ui->labelGpsLon->setText(command + " " + value);
        break;
    case GPS_GROUND_SPEED_KNOTS:
        ui->labelGpsSpeedKnots->setText(command + " " + value);
        break;
    case GPS_GROUND_SPEED_KMH:
        ui->labelGpsGroundSpeedKmH->setText(command + " " + value);
        break;
    case GPS_GROUND_COURSE:
        ui->labelGpsGroundSpeed->setText(command + " " + value);
        break;
    case GPS_NUM_SATS:
        ui->labelGpsNumberSats->setText(command + " " + value);
        break;
    case GPS_HDOP:
        ui->labelGpsGPS_HDOP->setText(command + " " + value);
        break;
    case IMU_ROLL:
        ui->labelRoll->setText(command + " " + value);
        break;
    case IMU_PITCH:
        ui->labelPitch->setText(command + " " + value);
        break;
    case IMU_HEADING:
        ui->labelHeading->setText(command + " " + value);
        break;
    case DHT22_TEMP:
        ui->labelDhtTemp->setText(command + " " + value);
        break;
    case DHT22_HUM:
        ui->labelDhtHumidity->setText(command + "  " + value);
        break;
    case VOLTAGE:
        ui->labelVoltage12v->setText(command + " " + value);
        break;
    case CURRENT:
        ui->labelSystemCurrent->setText(command + " " + value);
        break;
    case LED_RED:
        ui->labelRedLed->setText(command + " " + value);
        break;
    case LED_GREEN:
        ui->labelGreenLed->setText(command + " " + value);
        break;
    case LED_BLUE:
        ui->labelBlueLed->setText(command + " " + value);
        break;
    default:
        break;
    }
}



void AllSensorsDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}

void AllSensorsDialog::on_pushButtonAccCalibration_clicked()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Accelerometer Calibration",
                                                                tr("Please level the boat and sit still\nThen press yes to start calibration!"
                                                                   ""),
                                                                QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if(resBtn == QMessageBox::Yes)
    {

        //emit writeToSocket(tr(",%1,%2").arg(CommandString[ACC_ZERO]).arg(ValueString[ON]));

       // emit writeToSocket(tr(",%1,%2").arg(CommandString[ACC_ZERO]).arg(ValueString[ON]));

    }
    else
    {
        return;
    }

}

void AllSensorsDialog::on_pushButtonMagCalibration_clicked()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Magnetometer Calibration",
                                                                tr("Press Yes and magnetometer calibration will start!\n"
                                                                   "Please drive the boat in figure 8 for a couple of min!"
                                                                   ""),
                                                                QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if(resBtn == QMessageBox::Yes)
    {
       // emit writeToSocket(tr(",%1,%2").arg(CommandString[MAG_CALIBRATE]).arg(ValueString[ON]));

        QMessageBox::StandardButton resBt = QMessageBox::question( qobject_cast<QWidget *>(parent()), "Magnetometer Calibration",
                                                                    tr("Press Yes When you feel you are happy with your figure 8's\n"
                                                                       ""));



        if(resBt == QMessageBox::Yes || resBt == QMessageBox::No)
        {

             //emit writeToSocket(tr(",%1,%2").arg(CommandString[MAG_CALIBRATE]).arg(ValueString[OFF]));

             //4emit writeToSocket(tr(",%1,%2").arg(CommandString[MAG_CALIBRATE]).arg(ValueString[OFF]));

        }
        else
        {
           return;
        }



    }
    else
    {
        return;
    }

}
