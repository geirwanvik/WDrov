#ifndef INSTRUMENTFORM_H
#define INSTRUMENTFORM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>




namespace Ui {
class InstrumentForm;
}

class InstrumentForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstrumentForm(QWidget *parent = 0);
    ~InstrumentForm();

private slots:
    void on_pushButtonLatern_released();
    void on_pushButtonBilgePump_released();
    void on_pushButtonInteriorLights_released();
    void on_pushButtonWindowWiper_released();
    void on_pushButtonHeater_released();
    void on_pushButtonHorn_pressed();
    void on_pushButtonHorn_released();

    void on_pushButtonInstruments_clicked();

    void on_pushButtonFloodlight_clicked();

private:
    Ui::InstrumentForm *ui;
    void setupApperance();



signals:
    void writeToSocket(QString String);

public slots:
    void dataFromWdCore(QStringList StringList);

};

#endif // INSTRUMENTFORM_H
