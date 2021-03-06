#ifndef SENSOROVERVIEWFORM_H
#define SENSOROVERVIEWFORM_H

#include <QWidget>
#include <QPalette>
#include <QDebug>
#include <QStringList>
#include <QString>

#include "Scale/qscale.h"

#include "hmi/ConfigClasses/sensorconfigdialog.h"


namespace Ui {
class SensorOverviewForm;
}

class SensorOverviewForm : public QWidget
{
    Q_OBJECT

public:
    explicit SensorOverviewForm(QWidget *parent = 0);
    ~SensorOverviewForm();
    void showSensorConfig();

private:
    Ui::SensorOverviewForm *ui;

    QScale *mBatteryVoltageScale;
    QScale *mTempScale;
    QScale *mWaterTempScale;
    QScale *mHumidityScale;
    QScale *mRoll;
    QScale *mPitch;
    QScale *mGpsSpeed;
    QScale *mSystemCurrent;
    QScale *mSystemVoltage;

    void createBatteryVscale();
    void createTempScale();
    void createWaterTempScale();
    void createHumidityScale();
    void createRollScale();
    void createPitchScale();
    void createGpsSpeedScale();
    void createSystemCurrentScale();
    void createSystemVoltageScale();

    void createLayout();


    SensorConfigDialog *mSensorConfigView;

public slots:
    void imuData(QString command,QString value);
    void powerData(QString command,QString value);
    void dht22Data(QString command,QString value);
    void gpsData(QString command,QString value);


};

#endif // SENSOROVERVIEWFORM_H
