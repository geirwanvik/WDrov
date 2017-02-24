#ifndef SERIAL_SETUP_H
#define SERIAL_SETUP_H

#include <QDialog>

#include <QObject>
#include <QDialog>
#include <QIntValidator>
#include <QString>
#include <QSettings>

namespace Ui {
class serial_setup;
}

class serial_setup : public QDialog
{
    Q_OBJECT

public:
    explicit serial_setup(QWidget *parent = 0);
    ~serial_setup();
    QString getPort(void);
    qint32 getBaud(void);
    void setPort(QString);
    void setBaud(qint32);
    void GetPortInfo(void);

signals:
    void connectToPort(void);

private slots:
    void ValidateCustomBaud(int);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_portBox_highlighted(const QString &DataSting);

private:
    Ui::serial_setup *ui;

    QIntValidator *intValidator;
    void UpdateList(void);

    QString myPort;
    qint32 myBaud;

    void readSettings();
    void writeSettings();

public slots:
      void clearSettings(void);
};

#endif // SERIAL_SETUP_H
