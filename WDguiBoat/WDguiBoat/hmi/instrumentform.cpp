#include "instrumentform.h"
#include "ui_instrumentform.h"

InstrumentForm::InstrumentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstrumentForm)
{
    ui->setupUi(this);

    setupApperance();



}

InstrumentForm::~InstrumentForm()
{
    delete ui;
}


void InstrumentForm::setupApperance()
{
  /*  ui->pushButton_2->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton->setVisible(false);
*/
    ui->pushButtonBilgePump->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/bilge pump.png"));
    ui->pushButtonBilgePump->setIconSize(QSize(100,100));
    ui->pushButtonBilgePump->setCheckable(true);

    ui->pushButtonLatern->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/lantern.png"));
    ui->pushButtonLatern->setIconSize(QSize(100,100));
    ui->pushButtonLatern->setCheckable(true);

    ui->pushButtonInteriorLights->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/led light.png"));
    ui->pushButtonInteriorLights->setIconSize(QSize(100,100));
    ui->pushButtonInteriorLights->setCheckable(true);

    ui->pushButtonWindowWiper->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/windshield wiper.png"));
    ui->pushButtonWindowWiper->setIconSize(QSize(100,100));
    ui->pushButtonWindowWiper->setCheckable(true);

    ui->pushButtonHeater->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/heaterFan.png"));
    ui->pushButtonHeater->setIconSize(QSize(100,100));
    ui->pushButtonHeater->setCheckable(true);

    ui->pushButtonHorn->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/Horn.png"));
    ui->pushButtonHorn->setIconSize(QSize(100,100));
}

void InstrumentForm::showSensorConfig()
{

}

void InstrumentForm::on_pushButtonLatern_released()
{
    if(ui->pushButtonLatern->isChecked())
    {
        writeToSocket("RELAY_LANTERN,ON");
        ui->pushButtonLatern->setText("Lantern\nON");
        ui->pushButtonLatern->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("RELAY_LANTERN,OFF");
        ui->pushButtonLatern->setText("Lantern\nOFF");
        ui->pushButtonLatern->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonBilgePump_released()
{
    if(ui->pushButtonBilgePump->isChecked())
    {
        writeToSocket("RELAY_BILGE_PP,ON");
        ui->pushButtonBilgePump->setText("Bilge Pump\nON");
        ui->pushButtonBilgePump->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
       writeToSocket("RELAY_BILGE_PP,OFF");
       ui->pushButtonBilgePump->setText("Bilge Pump\nOFF");
       ui->pushButtonBilgePump->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonInteriorLights_released()
{
    if(ui->pushButtonInteriorLights->isChecked())
    {
        ui->pushButtonInteriorLights->setText("Interior Lights\nON");
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        ui->pushButtonInteriorLights->setText("Interior Lights\nOFF");
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonWindowWiper_released()
{
    if(ui->pushButtonWindowWiper->isChecked())
    {
        writeToSocket("RELAY_WIPER,ON");
        ui->pushButtonWindowWiper->setText("Window Wiper\nON");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("RELAY_WIPER,OFF");
        ui->pushButtonWindowWiper->setText("Window Wiper\nOFF");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton {}");
    }
}


void InstrumentForm::on_pushButtonHeater_released()
{
    if(ui->pushButtonHeater->isChecked())
    {
        ui->pushButtonHeater->setText("Heater\nON");
        ui->pushButtonHeater->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        ui->pushButtonHeater->setText("Heater\nOFF");
        ui->pushButtonHeater->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonHorn_pressed()
{
    ui->pushButtonHorn->setText("Horn\nTUUUUT!!");
    ui->pushButtonHorn->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
}

void InstrumentForm::on_pushButtonHorn_released()
{

    ui->pushButtonHorn->setText("Horn");
    ui->pushButtonHorn->setStyleSheet("QPushButton {}");
}
