#ifndef ALLSENSORSDIALOG_H
#define ALLSENSORSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QScroller>
#include "../../WDboat/CommandList.h"

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

private:
    Ui::AllSensorsDialog *ui;
    QScroller *scroller;
};

#endif // ALLSENSORSDIALOG_H
