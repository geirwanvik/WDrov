#ifndef ALLSENSORSDIALOG_H
#define ALLSENSORSDIALOG_H

#include <QDialog>
#include <QDebug>

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
    void sensorData(QStringList StringList);

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::AllSensorsDialog *ui;
};

#endif // ALLSENSORSDIALOG_H
