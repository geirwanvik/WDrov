#ifndef SENSOROVERVIEWFORM_H
#define SENSOROVERVIEWFORM_H

#include <QWidget>

#include "Scale/qscale.h"

namespace Ui {
class SensorOverviewForm;
}

class SensorOverviewForm : public QWidget
{
    Q_OBJECT

public:
    explicit SensorOverviewForm(QWidget *parent = 0);
    ~SensorOverviewForm();

private:
    Ui::SensorOverviewForm *ui;

    QScale *mVoltageScale;
    QScale *mTempScale;
    QScale *mRollScale;
    QScale *mPitchScale;
};

#endif // SENSOROVERVIEWFORM_H
