#include "sensorsetupdialog.h"
#include "ui_sensorsetupdialog.h"

SensorSetupDialog::SensorSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorSetupDialog)
{
    ui->setupUi(this);
    mRealTimer = new QTimer(this);
    connect(mRealTimer, SIGNAL(timeout()), this, SLOT(timerRequest()));

}

SensorSetupDialog::~SensorSetupDialog()
{
    delete ui;
}

void SensorSetupDialog::connectedToHost(bool status)
{
    if(status == true)
    {
        mRealTimer->start(500);
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
