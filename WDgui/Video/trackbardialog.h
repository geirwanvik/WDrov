#ifndef TRACKBARDIALOG_H
#define TRACKBARDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class trackBarDialog;
}

class trackBarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit trackBarDialog(QWidget *parent = 0);
    ~trackBarDialog();
    int H_MIN = 0;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 256;
    int V_MIN = 0;
    int V_MAX = 256;

private slots:
    void on_horizontalSliderH_Min_valueChanged(int value);

    void on_horizontalSliderH_Max_valueChanged(int value);

    void on_horizontalSliderS_Min_valueChanged(int value);

    void on_horizontalSliderS_Max_valueChanged(int value);

    void on_horizontalSliderV_Min_valueChanged(int value);

    void on_horizontalSliderV_Max_valueChanged(int value);

    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

private:
     Ui::trackBarDialog *ui;

};

#endif // TRACKBARDIALOG_H
