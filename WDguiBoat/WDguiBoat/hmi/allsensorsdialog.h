#ifndef ALLSENSORSDIALOG_H
#define ALLSENSORSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QScroller>
#include "../../WDboat/CommandList.h"
#include <QMessageBox>

namespace Ui {
class AllSensorsDialog;
}

class AllSensorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AllSensorsDialog(QWidget *parent = 0);
    ~AllSensorsDialog();

public slots:
    void sensorData(QString command,QString value);


private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonAccCalibration_clicked();
    void on_pushButtonMagCalibration_clicked();

private:
    Ui::AllSensorsDialog *ui;
    QScroller *scroller;

signals:
    void writeToSocket(QString String);

};

#endif // ALLSENSORSDIALOG_H
