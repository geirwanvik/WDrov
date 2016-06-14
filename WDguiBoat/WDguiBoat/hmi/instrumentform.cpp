#include "instrumentform.h"
#include "ui_instrumentform.h"

InstrumentForm::InstrumentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstrumentForm)
{
    ui->setupUi(this);

    setupApperance();
    mColorDialog = new ColorDialog(this);


}

InstrumentForm::~InstrumentForm()
{
    delete ui;
}

void InstrumentForm::showColorDialog()
{
    mColorDialog->setModal(true);
    mColorDialog->show();
}


void InstrumentForm::setupApperance()
{
    ui->pushButton_2->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->pushButton_6->setVisible(false);

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

    ui->pushButtonInstruments->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/instrument.png"));
    ui->pushButtonInstruments->setIconSize(QSize(100,100));
    ui->pushButtonInstruments->setCheckable(true);

    ui->pushButtonFloodlight->setCheckable(true);
    ui->pushButtonFloodlight->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/searchlight.png"));
    ui->pushButtonFloodlight->setIconSize(QSize(100,100));
}

void InstrumentForm::dataFromWdCore(QString command, QString value)
{
    qDebug() << "Instrument: " << command << " " << value;
}


void InstrumentForm::on_pushButtonLatern_released()
{
    if(ui->pushButtonLatern->isChecked())
    {
        writeToSocket("ARDU,RELAY_LANTERN,ON");
        ui->pushButtonLatern->setText("Lantern\nON");
        ui->pushButtonLatern->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("ARDU,RELAY_LANTERN,OFF");
        ui->pushButtonLatern->setText("Lantern\nOFF");
        ui->pushButtonLatern->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonBilgePump_released()
{
    if(ui->pushButtonBilgePump->isChecked())
    {
        writeToSocket("ARDU,RELAY_BILGE_PP,ON");
        ui->pushButtonBilgePump->setText("Bilge Pump\nON");
        ui->pushButtonBilgePump->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
       writeToSocket("ARDU,RELAY_BILGE_PP,OFF");
       ui->pushButtonBilgePump->setText("Bilge Pump\nOFF");
       ui->pushButtonBilgePump->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonInteriorLights_released()
{
    if(ui->pushButtonInteriorLights->isChecked())
    {
        writeToSocket("ARDU,RED_LED,255,GREEN_LED,255,BLUE_LED,255");
        ui->pushButtonInteriorLights->setText("Interior Lights\nON");
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("ARDU,RED_LED,0,GREEN_LED,0,BLUE_LED,0");
        ui->pushButtonInteriorLights->setText("Interior Lights\nOFF");
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonWindowWiper_released()
{
    if(ui->pushButtonWindowWiper->isChecked())
    {
        writeToSocket("ARDU,RELAY_WIPER,ON");
        ui->pushButtonWindowWiper->setText("Window Wiper\nON");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("ARDU,RELAY_WIPER,OFF");
        ui->pushButtonWindowWiper->setText("Window Wiper\nOFF");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton {}");
    }
}


void InstrumentForm::on_pushButtonHeater_released()
{
    if(ui->pushButtonHeater->isChecked())
    {
        writeToSocket("ARDU,HEATER,ON");
        ui->pushButtonHeater->setText("Heater\nON");
        ui->pushButtonHeater->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("ARDU,HEATER,OFF");
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

void InstrumentForm::on_pushButtonInstruments_clicked()
{
    if(ui->pushButtonInstruments->isChecked())
    {
        writeToSocket("ARDU,INSTRUMENT,ON");
        ui->pushButtonInstruments->setText("Instrument\nPower ON");
        ui->pushButtonInstruments->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");
    }
    else
    {
        writeToSocket("ARDU,INSTRUMENT,OFF");
        ui->pushButtonInstruments->setText("Instrument\nPower OFF");
        ui->pushButtonInstruments->setStyleSheet("QPushButton {}");
    }
}

void InstrumentForm::on_pushButtonFloodlight_clicked()
{
    if(ui->pushButtonFloodlight->isChecked())
    {
        ui->pushButtonFloodlight->setText("Floodlight\nON");
        ui->pushButtonFloodlight->setStyleSheet("QPushButton { background-color: rgb(0, 255, 0);border-radius: 11px; border: 2px solid #555;}");

    }
    else
    {
        ui->pushButtonFloodlight->setText("Floodlight\nOFF");
        ui->pushButtonFloodlight->setStyleSheet("QPushButton {}");
    }
}
