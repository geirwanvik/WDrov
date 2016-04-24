#include "sensoroverviewform.h"
#include "ui_sensoroverviewform.h"

SensorOverviewForm::SensorOverviewForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorOverviewForm)
{
    ui->setupUi(this);

    mVoltageScale = new QScale(this);
    mVoltageScale->setMaximum(16);
    mVoltageScale->setMinimum(0);
    mVoltageScale->setLabelsVisible(true);
    mVoltageScale->setLabelsFormat('V', 1);
    ui->verticalLayoutVoltage->addWidget(mVoltageScale);

    mTempScale = new QScale(this);
    mTempScale->setRange(-25,50);
    ui->verticalLayoutTemp->addWidget(mTempScale);

    mRollScale = new QScale(this);
    mRollScale->setRange(-90, 90);
    ui->verticalLayoutRoll->addWidget(mRollScale);

    mPitchScale = new QScale(this);
    mPitchScale->setRange(-90, 90);
    ui->verticalLayoutPitch->addWidget(mPitchScale);
}

SensorOverviewForm::~SensorOverviewForm()
{
    delete ui;
}
