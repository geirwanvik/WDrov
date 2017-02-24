#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include <QTime>
#include <QDate>

#include "Plot/Lib/qcustomplot.h"

namespace Ui {
class plotDialog;
}

class plotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit plotDialog(QWidget *parent = 0);
    ~plotDialog();

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonApply_clicked();

private:
    Ui::plotDialog *ui;

public slots:
    void plotData(QString cmd, QString value);
};

#endif // PLOTDIALOG_H
