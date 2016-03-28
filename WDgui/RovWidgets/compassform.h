#ifndef COMPASSFORM_H
#define COMPASSFORM_H

#include <QWidget>
#include <QDebug>
#include "RovWidgets/source/qcgaugewidget.h"

namespace Ui {
class CompassForm;
}

class CompassForm : public QWidget
{
    Q_OBJECT

public:
    explicit CompassForm(QWidget *parent = 0);
    ~CompassForm();

public slots:

     void sensorData(QString cmd, QString Value);

private:
    Ui::CompassForm *ui;
    void on_Compass_valueChanged(int value);
    QcGaugeWidget * mCompassGauge;
    QcNeedleItem *mCompassNeedle;


};

#endif // COMPASSFORM_H
