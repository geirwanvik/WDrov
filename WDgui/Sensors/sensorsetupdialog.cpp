#include "sensorsetupdialog.h"
#include "ui_sensorsetupdialog.h"

SensorSetupDialog::SensorSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorSetupDialog)
{
    ui->setupUi(this);
    mRealTimer = new QTimer(this);
    connect(mRealTimer, SIGNAL(timeout()), this, SLOT(timerRequest()));

    readSettings();

    ui->lineEditUpdateRate->setText(QString::number(getUpdateRateMs()));

    qDebug () << "Update Rate sett to: " << getUpdateRateMs() << " ms";

    ui->checkBoxHeading->setEnabled(false);
    ui->checkBoxPitch->setEnabled(false);
    ui->checkBoxRoll->setEnabled(false);

    ui->checkBoxHeading->setChecked(true);
    ui->checkBoxPitch->setChecked(true);
    ui->checkBoxRoll->setChecked(true);

}

SensorSetupDialog::~SensorSetupDialog()
{
    delete ui;
}

void SensorSetupDialog::writeSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_Stensor");
    settings.setValue("updateRate", updateRateMs);
    settings.endGroup();
}

void SensorSetupDialog::readSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_Stensor");
    updateRateMs = settings.value("updateRate", updateRateMs).toInt();
    settings.endGroup();
}

quint32 SensorSetupDialog::getUpdateRateMs() const
{
    return updateRateMs;
}

void SensorSetupDialog::setUpdateRateMs(const quint32 &value)
{
    updateRateMs = value;
}

void SensorSetupDialog::connectedToHost(bool status)
{
    if(status == true)
    {
        mRealTimer->start(ui->lineEditUpdateRate->text().toInt());
        qDebug() << "Real Timer Started!";
    }
    else
    {
        mRealTimer->stop();
    }
}

void SensorSetupDialog::timerRequest()
{

    emit requestSensorData(",ROLL,READ,PITCH,READ,HEADING,READ");

}



void SensorSetupDialog::on_pushButtonSaveAndClose_clicked()
{
    setUpdateRateMs(ui->lineEditUpdateRate->text().toInt());
    mRealTimer->start(getUpdateRateMs());
    writeSettings();

    this->hide();

}

void SensorSetupDialog::on_pushButtonCancel_clicked()
{
    this->hide();
}
