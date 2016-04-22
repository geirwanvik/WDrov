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
    ui->pushButton_2->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton->setVisible(false);

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

void InstrumentForm::on_pushButtonLatern_released()
{
    if(ui->pushButtonLatern->isChecked())
    {
        ui->pushButtonLatern->setText("Lantern\nON");
    }
    else
    {
        ui->pushButtonLatern->setText("Lantern\nOFF");
    }
}

void InstrumentForm::on_pushButtonBilgePump_released()
{
    if(ui->pushButtonBilgePump->isChecked())
    {
        ui->pushButtonBilgePump->setText("Bilge Pump\nON");
    }
    else
    {
       ui->pushButtonBilgePump->setText("Bilge Pump\nOFF");
    }
}

void InstrumentForm::on_pushButtonInteriorLights_released()
{
    if(ui->pushButtonInteriorLights->isChecked())
    {
        ui->pushButtonInteriorLights->setText("Interior Lights\nON");
    }
    else
    {
        ui->pushButtonInteriorLights->setText("Interior Lights\nOFF");
    }
}

void InstrumentForm::on_pushButtonWindowWiper_released()
{
    if(ui->pushButtonWindowWiper->isChecked())
    {
        ui->pushButtonWindowWiper->setText("Window Wiper\nON");
    }
    else
    {
        ui->pushButtonWindowWiper->setText("Window Wiper\nOFF");
    }
}


void InstrumentForm::on_pushButtonHeater_released()
{
    if(ui->pushButtonHeater->isChecked())
    {
        ui->pushButtonHeater->setText("Heater\nON");
    }
    else
    {
        ui->pushButtonHeater->setText("Heater\nOFF");
    }
}

void InstrumentForm::on_pushButtonHorn_pressed()
{
    qDebug() << "Pressed!";
    ui->pushButtonHorn->setText("Horn\nTUUUUT!!");
}

void InstrumentForm::on_pushButtonHorn_released()
{
    qDebug() << "Released!";
    ui->pushButtonHorn->setText("Horn");
}
