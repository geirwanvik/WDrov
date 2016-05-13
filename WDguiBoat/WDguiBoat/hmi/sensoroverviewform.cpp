#include "sensoroverviewform.h"
#include "ui_sensoroverviewform.h"

SensorOverviewForm::SensorOverviewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorOverviewForm)
{
    ui->setupUi(this);

    mSensorConfigView = new SensorConfigDialog(this);

    createBatteryVscale();
    createTempScale();
    createWaterTempScale();
    createHumidityScale();


}

SensorOverviewForm::~SensorOverviewForm()
{
    delete ui;
}

void SensorOverviewForm::showSensorConfig()
{
    mSensorConfigView->show();
}

void SensorOverviewForm::createBatteryVscale()
{
    mBatteryVoltageScale = new QScale(this);
    mBatteryVoltageScale->setRange(8,16);
    mBatteryVoltageScale->setLabelsVisible(true);
    mBatteryVoltageScale->setLabelsFormat('V', 0);
    ui->verticalLayoutFirstView->addWidget(mBatteryVoltageScale);
}

void SensorOverviewForm::createTempScale()
{
    mTempScale = new QScale(this);
    mTempScale->setRange(-25,50);
    ui->groupBoxSecondView->setTitle(" Temperature");
    ui->verticalLayoutSecondView->addWidget(mTempScale);
}

void SensorOverviewForm::createWaterTempScale()
{

    mWaterTempScale = new QScale(this);
    mWaterTempScale->setRange(-5, 40);
    ui->groupBoxThirdView->setTitle(" Water Temperature");
    ui->verticalLayoutThirdView->addWidget(mWaterTempScale);
}

void SensorOverviewForm::createHumidityScale()
{
    mHumidityScale = new QScale(this);
    mHumidityScale->setRange(0, 100);
    ui->groupBoxFourthView->setTitle(" Humidity");
    ui->verticalLayoutFourtView->addWidget(mHumidityScale);
}

void SensorOverviewForm::createRollScale()
{
    mRoll = new QScale(this);
    mRoll->setRange(-30, 30);
    ui->groupBoxThirdView->setTitle(" Roll");
    ui->verticalLayoutThirdView->addWidget(mRoll);
}

void SensorOverviewForm::createPitchScale()
{
    mPitch = new QScale(this);
    mPitch->setRange(-30, 30);
    ui->groupBoxFourthView->setTitle(" Pitch");
    ui->verticalLayoutFourtView->addWidget(mPitch);
}

void SensorOverviewForm::createGpsSpeedScale()
{
    mGpsSpeed = new QScale(this);
    mGpsSpeed->setRange(-5,20);
    ui->groupBoxFourthView->setTitle(" GPS Speed Over Ground");
    ui->verticalLayoutFourtView->addWidget(mGpsSpeed);
}

void SensorOverviewForm::createSystemCurrentScale()
{
    mSystemCurrent = new QScale(this);
    mSystemCurrent->setRange(0, 10);
    ui->groupBoxFirstView->setTitle(" System Current");
    ui->verticalLayoutFirstView->addWidget(mSystemCurrent);
}

void SensorOverviewForm::createSystemVoltageScale()
{
    mSystemVoltage = new QScale(this);
    mSystemVoltage->setRange(0,6);
    ui->groupBoxSecondView->setTitle(" System Voltage");
    ui->verticalLayoutSecondView->addWidget(mSystemVoltage);
}

void SensorOverviewForm::createLayout()
{

}
