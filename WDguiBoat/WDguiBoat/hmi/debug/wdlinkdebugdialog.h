#ifndef WDLINKDEBUGDIALOG_H
#define WDLINKDEBUGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QScroller>

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
    QScroller *scroller;

public slots:
    void wdLinkData(QString command, QString value);
    void wdlinkRaw(QString string);

signals:
    void writeToSocket(QString string);

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonSend_clicked();
};

#endif // WDLINKDEBUGDIALOG_H
