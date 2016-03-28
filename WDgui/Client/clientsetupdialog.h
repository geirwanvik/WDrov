#ifndef CLIENTSETUPDIALOG_H
#define CLIENTSETUPDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

namespace Ui {
class clientSetupDialog;
}

class clientSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit clientSetupDialog(QWidget *parent = 0);
    ~clientSetupDialog();

    QString getIpAdress() const;
    void setIpAdress(const QString &value);

    quint32 getPort() const;
    void setPort(const quint32 &value);

private slots:
    void on_pushButtonSaveClose_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::clientSetupDialog *ui;
    QString ipAdress;
    quint32 port;

    void writeSettings();
    void readSettings();
};

#endif // CLIENTSETUPDIALOG_H
