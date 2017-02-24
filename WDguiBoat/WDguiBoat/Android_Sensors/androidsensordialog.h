#ifndef ANDROIDSENSORDIALOG_H
#define ANDROIDSENSORDIALOG_H

#include <QDialog>

#include "Android_Sensors/androidgps.h"
#include "Android_Sensors/androidaccelerometer.h"
#include "Android_Sensors/androidcompass.h"
#include "Android_Sensors/lightsensor.h"


namespace Ui {
class AndroidSensorDialog;
}

class AndroidSensorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AndroidSensorDialog(QWidget *parent = 0);
    ~AndroidSensorDialog();

private slots:
    void on_pushButtonClose_clicked();
    void lightSensorData();
    void accSensorData();
    void gyroSensorData();
    void headingData();

private:
    Ui::AndroidSensorDialog *ui;
    androidGps *mAndroidGpsSource;
    androidAccelerometer *mAndroidAccelerometer;
    androidCompass *mCompass;
    lightSensor *mLightSensor;

    quint32 Lux;

    qreal accX;
    qreal accY;
    qreal accZ;

    qreal gyroX;
    qreal gyroY;
    qreal gyroZ;

    qreal azimuth;

};

#endif // ANDROIDSENSORDIALOG_H
