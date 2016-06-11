#ifndef WDLINKDEBUGDIALOG_H
#define WDLINKDEBUGDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class wdLinkDebugDialog;
}

class wdLinkDebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit wdLinkDebugDialog(QWidget *parent = 0);
    ~wdLinkDebugDialog();

private:
    Ui::wdLinkDebugDialog *ui;

public slots:
    void wdLinkData(QString command, QString value);

signals:
    void writeDataToConsole(QString command, QString value);
private slots:
    void on_pushButtonClose_clicked();
};

#endif // WDLINKDEBUGDIALOG_H
