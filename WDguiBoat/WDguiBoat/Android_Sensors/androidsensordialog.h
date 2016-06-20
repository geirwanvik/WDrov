#ifndef ANDROIDSENSORDIALOG_H
#define ANDROIDSENSORDIALOG_H

#include <QDialog>

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

private:
    Ui::AndroidSensorDialog *ui;
};

#endif // ANDROIDSENSORDIALOG_H
