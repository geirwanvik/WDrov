#ifndef SENSORCONFIGDIALOG_H
#define SENSORCONFIGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QButtonGroup>

namespace Ui {
class SensorConfigDialog;
}

class SensorConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorConfigDialog(QWidget *parent = 0);
    ~SensorConfigDialog();
    QButtonGroup firstButtonGroup;
    QButtonGroup secondButtonGroup;
    QButtonGroup thirdButtonGroup;
    QButtonGroup fourthButtonGroup;

private slots:
    void on_pushButtonSaveAndClose_clicked();

private:
    Ui::SensorConfigDialog *ui;
    void readSetting();
    void writeSetting();
    void groupRadioButtons();
};

#endif // SENSORCONFIGDIALOG_H
