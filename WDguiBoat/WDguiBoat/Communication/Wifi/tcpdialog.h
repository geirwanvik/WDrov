#ifndef TCPDIALOG_H
#define TCPDIALOG_H

#include "crccnode.h"

#include <QDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class TcpDialog;
}

class TcpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TcpDialog(QWidget *parent = 0);
    ~TcpDialog();

private slots:


    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

    void on_checkBox_clicked();

private:
    Ui::TcpDialog *ui;
    QTcpSocket *mTcpSocket;
    QHostAddress *IpAdress;
    quint16 port;

   void requestCnodeData(qint8 messageID, qint8 op, char typeCmd, QTcpSocket *r_serial);
};

#endif // TCPDIALOG_H
