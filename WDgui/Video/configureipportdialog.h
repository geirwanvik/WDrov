#ifndef CONFIGUREIPPORTDIALOG_H
#define CONFIGUREIPPORTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QDebug>

namespace Ui {
class ConfigureIpPortDialog;
}

class ConfigureIpPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureIpPortDialog(QWidget *parent = 0);
    ~ConfigureIpPortDialog();

    QString getIpAdress() const;
    void setIpAdress(const QString &value);

    quint32 getPort() const;
    void setPort(const quint32 &value);

    QString getHttpAdress() const;
    void setHttpAdress(const QString &value);

    quint16 getWebCameraNumber() const;
    void setWebCameraNumber(const quint16 &value);

    QString getTypeStream() const;
    void setTypeStream(const QString &value);

private slots:
    void on_pushButtonSaveAndClose_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ConfigureIpPortDialog *ui;
    QString ipAdress;
    quint32 port;
    QString httpAdress;
    quint16 webCameraNumber;
    QString typeStream;
    void writeSettings();
    void readSettings();
    void setupApperance();
    void setStreamType();
};

#endif // CONFIGUREIPPORTDIALOG_H
