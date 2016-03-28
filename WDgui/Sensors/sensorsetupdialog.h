#ifndef SENSORSETUPDIALOG_H
#define SENSORSETUPDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>


namespace Ui {
class SensorSetupDialog;
}

class SensorSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorSetupDialog(QWidget *parent = 0);
    ~SensorSetupDialog();

private:
    Ui::SensorSetupDialog *ui;
    QTimer *mRealTimer;

public slots:
    void connectedToHost(bool status);


private slots:
    void timerRequest();

signals:
    void requestSensorData(QString String);

};

#endif // SENSORSETUPDIALOG_H
