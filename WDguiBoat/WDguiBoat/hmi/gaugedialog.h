#ifndef GAUGEDIALOG_H
#define GAUGEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <gaugeWidgets/qcgaugewidget.h>
#include "../../WDboat/CommandList.h"

namespace Ui {
class gaugeDialog;
}

class gaugeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gaugeDialog(QWidget *parent = 0);
    ~gaugeDialog();

private:
    Ui::gaugeDialog *ui;
    QcGaugeWidget *mCompassGauge;
    QcNeedleItem *mCompassNeedle;

    void apperanceSetup();

public slots:
    void gpsData(QString command,QString value);
    void dht22Data(QString command,QString value);
    void imuData(QString command,QString value);
};

#endif // GAUGEDIALOG_H
