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
    mBatteryVoltageScale->setRange(6,16);
    mBatteryVoltageScale->setValue(10);
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



void SensorOverviewForm::imuData(QString command, QString value)
{
    if(command == "IMU_ROLL")
    {
         QString RollValue = value;
         mRoll->setValue(RollValue.toDouble());
    }
    else if(command == "IMU_PITCH")
    {
        QString pitchValue = value;
        mPitch->setValue(pitchValue.toDouble());
    }
    else
    {
        return;
    }
}

void SensorOverviewForm::powerData(QString command, QString value)
{
    createLayout();

    if(command == "VOLTAGE")
    {
         QString voltage = value;
         mBatteryVoltageScale->setValue(voltage.toDouble());
    }
    else if(command == "CURRENT")
    {
        QString systemCurrent = value;
        mSystemCurrent->setValue(systemCurrent.toDouble());
    }
    else
    {
        return;
    }
}

void SensorOverviewForm::dht22Data(QString command, QString value)
{
    if(command == "DHT22_TEMP")
    {
         QString temp = value;
         mTempScale->setValue(temp.toDouble());
    }
    else if(command == "DHT22_HUM")
    {
        QString humidity = value;
        mHumidityScale->setValue(humidity.toDouble());
    }
    else
    {
        return;
    }
}

void SensorOverviewForm::gpsData(QString command, QString value)
{
    if(command == "GPS_GROUND_SPEED")
    {
        QString GpsGroundSpeed = value;
        mGpsSpeed->setValue(GpsGroundSpeed.toDouble());
    }
    else
    {
        return;
    }
}
