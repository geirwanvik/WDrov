#ifndef ATTTUDEINDICATORFORM_H
#define ATTTUDEINDICATORFORM_H

#include <QWidget>
#include "source/qcgaugewidget.h"

namespace Ui {
class AtttudeIndicatorForm;
}

class AtttudeIndicatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit AtttudeIndicatorForm(QWidget *parent = 0);
    ~AtttudeIndicatorForm();

public slots:

    void sensorData(QString cmd, QString Value);

private:
    Ui::AtttudeIndicatorForm *ui;

    QcGaugeWidget * mAttitudeGauge;
    QcNeedleItem * mAttitudeNeedle;
    QcAttitudeMeter *mAttMeter;

    void on_horizontal_valueChanged(int value);
    void on_vertical_valueChanged(int value);
};

#endif // ATTTUDEINDICATORFORM_H
