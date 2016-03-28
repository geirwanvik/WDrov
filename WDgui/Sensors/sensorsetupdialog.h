#ifndef SENSORSETUPDIALOG_H
#define SENSORSETUPDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDebug>
#include <QSettings>


namespace Ui {
class SensorSetupDialog;
}

class SensorSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorSetupDialog(QWidget *parent = 0);
    ~SensorSetupDialog();

    quint32 getUpdateRateMs() const;
    void setUpdateRateMs(const quint32 &value);

private:
    Ui::SensorSetupDialog *ui;
    QTimer *mRealTimer;

    void writeSettings();
    void readSettings();

    quint32 updateRateMs;

public slots:
    void connectedToHost(bool status);


private slots:
    void timerRequest();

    void on_pushButtonSaveAndClose_clicked();

    void on_pushButtonCancel_clicked();

signals:
    void requestSensorData(QString String);

};

#endif // SENSORSETUPDIALOG_H
