#include "androidsensordialog.h"
#include "ui_androidsensordialog.h"

AndroidSensorDialog::AndroidSensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AndroidSensorDialog)
{
    ui->setupUi(this);
#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else
    this->resize(1000,750);
#endif

    //  mAndroidGpsSource = new androidGps(this);
        mAndroidAccelerometer = new androidAccelerometer(this);
        connect(mAndroidAccelerometer->accmeter, SIGNAL(readingChanged()), this, SLOT(accSensorData()));

        mCompass = new androidCompass(this);
        connect(mCompass->mCompass, SIGNAL(readingChanged()), this, SLOT(headingData()));

        mLightSensor = new lightSensor(this);
        connect(mLightSensor->mLightSensor, SIGNAL(readingChanged()), this, SLOT(lightSensorData()));

}

AndroidSensorDialog::~AndroidSensorDialog()
{
    delete ui;
}

void AndroidSensorDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}

void AndroidSensorDialog::lightSensorData()
{
    Lux = mLightSensor->mLightSensor->reading()->lux();
    ui->labelLightLux->setText(tr("Light Value (LUX): %1").arg(Lux));

}

void AndroidSensorDialog::accSensorData()
{
    accX = mAndroidAccelerometer->accmeter->reading()->x();
    accY = mAndroidAccelerometer->accmeter->reading()->y();
    accZ = mAndroidAccelerometer->accmeter->reading()->z();

    ui->labelAccX->setText(tr("Acc X: %1").arg(accX));
    ui->labelAccY->setText(tr("Acc Y: %1").arg(accY));
    ui->labelAccZ->setText(tr("Acc Z: %1").arg(accZ));

}

void AndroidSensorDialog::gyroSensorData()
{

}

void AndroidSensorDialog::headingData()
{
    azimuth = mCompass->mCompass->reading()->azimuth();
    ui->labelHeadingAzimuth->setText(tr("Azimuth: %1").arg(azimuth));
}
