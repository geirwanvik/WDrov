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
    createRollScale();
    createPitchScale();
    createGpsSpeedScale();
    createSystemCurrentScale();
    createSystemVoltageScale();

    createLayout();

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
    mBatteryVoltageScale->setVisible(false);
    ui->verticalLayoutFirstView->addWidget(mBatteryVoltageScale);
}

void SensorOverviewForm::createTempScale()
{
    mTempScale = new QScale(this);
    mTempScale->setRange(-25,50);
    mTempScale->setLabelsFormat('V', 1);
    ui->groupBoxSecondView->setTitle(" Temperature");
    mTempScale->setVisible(false);
    ui->verticalLayoutSecondView->addWidget(mTempScale);
}

void SensorOverviewForm::createWaterTempScale()
{

    mWaterTempScale = new QScale(this);
    mWaterTempScale->setRange(-5, 40);
    ui->groupBoxThirdView->setTitle(" Water Temperature");
    mWaterTempScale->setVisible(false);
    ui->verticalLayoutThirdView->addWidget(mWaterTempScale);
}

void SensorOverviewForm::createHumidityScale()
{
    mHumidityScale = new QScale(this);
    mHumidityScale->setRange(0, 100);
    ui->groupBoxFourthView->setTitle(" Humidity");
    mHumidityScale->setVisible(false);
    ui->verticalLayoutFirstView->addWidget(mHumidityScale);
}

void SensorOverviewForm::createRollScale()
{
    mRoll = new QScale(this);
    mRoll->setRange(-30, 30);
    ui->groupBoxThirdView->setTitle(" Roll");
    mRoll->setVisible(false);
    ui->verticalLayoutThirdView->addWidget(mRoll);
}

void SensorOverviewForm::createPitchScale()
{
    mPitch = new QScale(this);
    mPitch->setRange(-30, 30);
    ui->groupBoxFourthView->setTitle(" Pitch");
    mPitch->setVisible(false);
    ui->verticalLayoutFourtView->addWidget(mPitch);
}

void SensorOverviewForm::createGpsSpeedScale()
{
    mGpsSpeed = new QScale(this);
    mGpsSpeed->setRange(-5,20);
    mGpsSpeed->setVisible(false);
    ui->verticalLayoutFourtView->addWidget(mGpsSpeed);
}

void SensorOverviewForm::createSystemCurrentScale()
{
    mSystemCurrent = new QScale(this);
    mSystemCurrent->setRange(0, 10);
    mSystemCurrent->setVisible(false);
    ui->verticalLayoutFirstView->addWidget(mSystemCurrent);
}

void SensorOverviewForm::createSystemVoltageScale()
{
    mSystemVoltage = new QScale(this);
    mSystemVoltage->setRange(0,6);
    mSystemVoltage->setVisible(false);
    ui->verticalLayoutSecondView->addWidget(mSystemVoltage);
}

void SensorOverviewForm::createLayout()
{


    if(mSensorConfigView->firstButtonGroup.checkedButton()->text() == "Battery Voltage")
    {
        mSystemCurrent->setVisible(false);
        mHumidityScale->setVisible(false);
        mBatteryVoltageScale->setVisible(true);
        ui->groupBoxFirstView->setTitle("Battery Voltage");
    }
    else if(mSensorConfigView->firstButtonGroup.checkedButton()->text() == "System Current")
    {
        mSystemCurrent->setVisible(true);
        mHumidityScale->setVisible(false);
        mBatteryVoltageScale->setVisible(false);
        ui->groupBoxFirstView->setTitle("System Current");
    }
    else if(mSensorConfigView->firstButtonGroup.checkedButton()->text() == "Humidity")
    {
        mSystemCurrent->setVisible(false);
        mHumidityScale->setVisible(true);
        mBatteryVoltageScale->setVisible(false);
        ui->groupBoxFirstView->setTitle("Humidity");
    }
    else
    {
        return;
    }

    //Second groupBox
    if(mSensorConfigView->secondButtonGroup.checkedButton()->text() == "Temperature")
    {
        mTempScale->setVisible(true);
        mSystemVoltage->setVisible(false);
        ui->groupBoxSecondView->setTitle("Temperature");
    }
    else if(mSensorConfigView->secondButtonGroup.checkedButton()->text() == "System Voltage")
    {
        mTempScale->setVisible(false);
        mSystemVoltage->setVisible(true);
        ui->groupBoxSecondView->setTitle("System Voltage");
    }
    else
    {
        return;
    }
    //Third groupbox
    if(mSensorConfigView->thirdButtonGroup.checkedButton()->text() == "Roll")
    {
        mRoll->setVisible(true);
        mWaterTempScale->setVisible(false);
        ui->groupBoxThirdView->setTitle("Roll");
    }
    else if(mSensorConfigView->thirdButtonGroup.checkedButton()->text() == "Water Temperature")
    {
        mRoll->setVisible(false);
        mWaterTempScale->setVisible(true);
        ui->groupBoxThirdView->setTitle("Water Temperature");
    }
    else
    {
        return;
    }

    //Fourth groupBox
    if(mSensorConfigView->fourthButtonGroup.checkedButton()->text() == "Pitch")
    {
        mPitch->setVisible(true);
        mGpsSpeed->setVisible(false);
        ui->groupBoxFourthView->setTitle("Pitch");
    }
    else if(mSensorConfigView->fourthButtonGroup.checkedButton()->text() == "GPS Speed Over Ground")
    {
        mPitch->setVisible(false);
        mGpsSpeed->setVisible(true);
        ui->groupBoxFourthView->setTitle("GPS Speed Of Ground");
    }
    else
    {
        return;
    }

}

void SensorOverviewForm::sensorData(QStringList StringList)
{
    createLayout();

    if(StringList.contains("GPS_LAT") || StringList.contains("GPS_LON"))
    {
      //  qDebug() << StringList[6] << StringList[7] << StringList[8] << StringList[9];
        QString GpsGroundSpeed = StringList[7];
       // QString Gps3Dspeed = StringList[9];
        mGpsSpeed->setValue(GpsGroundSpeed.toDouble());
    }
    else if(StringList.contains("IMU_ROLL") || StringList.contains("IMU_PITCH"))
    {
       // qDebug() << StringList[0] << StringList[1] << StringList[2] << StringList[3];
        QString RollValue = StringList[1];
        QString pitchValue = StringList[3];
        mRoll->setValue(RollValue.toDouble());
        mPitch->setValue(pitchValue.toDouble());
    }
    else if(StringList.contains("DHT22_TEMP") || StringList.contains("DHT22_HUM"))
    {
        //qDebug() << StringList[0] << StringList[1] << StringList[2] << StringList[3];
        QString temp = StringList[1];
        QString humidity = StringList[3];
        mTempScale->setValue(temp.toDouble());
        mHumidityScale->setValue(humidity.toDouble());
    }
}
