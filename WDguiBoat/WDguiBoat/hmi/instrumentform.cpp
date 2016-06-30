#include "instrumentform.h"
#include "ui_instrumentform.h"

InstrumentForm::InstrumentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstrumentForm)
{
    ui->setupUi(this);

    setupApperance();
    mColorDialog = new ColorDialog(this);
/*
    ui->pushButtonBilgePump->setStyle(new styleOne);
    ui->pushButtonFloodlight->setStyle(new styleOne);
    ui->pushButtonHeater->setStyle(new styleOne);
    ui->pushButtonHorn->setStyle(new styleOne);
    ui->pushButtonInstruments->setStyle(new styleOne);
    ui->pushButtonInteriorLights->setStyle(new styleOne);
    ui->pushButtonLatern->setStyle(new styleOne);
    ui->pushButtonWindowWiper->setStyle(new styleOne);

*/
    ui->pushButtonLatern->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonBilgePump->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonFloodlight->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonHeater->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonInteriorLights->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonWindowWiper->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonHorn->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    ui->pushButtonInstruments->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");

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

void InstrumentForm::connectedToWdCore(bool status)
{
    ui->pushButtonLatern->setEnabled(status);
    ui->pushButtonBilgePump->setEnabled(status);
    ui->pushButtonHeater->setEnabled(status);
    ui->pushButtonInstruments->setEnabled(status);
    ui->pushButtonInteriorLights->setEnabled(status);
    ui->pushButtonWindowWiper->setEnabled(status);
    ui->pushButtonFloodlight->setEnabled(status);
    ui->pushButtonHorn->setEnabled(status);
}


void InstrumentForm::setupApperance()
{


    ui->pushButtonBilgePump->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/bilge pump.png"));
    ui->pushButtonBilgePump->setIconSize(QSize(140,140));
    ui->pushButtonBilgePump->setCheckable(true);

    ui->pushButtonLatern->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/lantern.png"));
    ui->pushButtonLatern->setIconSize(QSize(140,140));
    ui->pushButtonLatern->setCheckable(true);

    ui->pushButtonInteriorLights->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/led light.png"));
    ui->pushButtonInteriorLights->setIconSize(QSize(140,140));
    ui->pushButtonInteriorLights->setCheckable(true);

    ui->pushButtonWindowWiper->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/windshield wiper.png"));
    ui->pushButtonWindowWiper->setIconSize(QSize(140,140));
    ui->pushButtonWindowWiper->setCheckable(true);

    ui->pushButtonHeater->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/heaterFan.png"));
    ui->pushButtonHeater->setIconSize(QSize(140,140));
    ui->pushButtonHeater->setCheckable(true);

    ui->pushButtonHorn->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/Horn.png"));
    ui->pushButtonHorn->setIconSize(QSize(140,140));

    ui->pushButtonInstruments->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/instrument.png"));
    ui->pushButtonInstruments->setIconSize(QSize(140,140));
    ui->pushButtonInstruments->setCheckable(true);

    ui->pushButtonFloodlight->setCheckable(true);
    ui->pushButtonFloodlight->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/searchlight.png"));
    ui->pushButtonFloodlight->setIconSize(QSize(140,140));

}

void InstrumentForm::dataFromWdCore(QString command, QString value)
{
    qDebug() << "Instrument: " << command << " " << value;
}


void InstrumentForm::on_pushButtonLatern_released()
{
    if(ui->pushButtonLatern->isChecked())
    {
        writeToSocket(",RELAY_LANTERN,ON");
        ui->pushButtonLatern->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {
      writeToSocket(",RELAY_LANTERN,OFF");
      ui->pushButtonLatern->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");

    }
}

void InstrumentForm::on_pushButtonBilgePump_released()
{
    if(ui->pushButtonBilgePump->isChecked())
    {
        ui->pushButtonBilgePump->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
        writeToSocket(",RELAY_BILGE_PP,ON");

    }
    else
    {
       writeToSocket(",RELAY_BILGE_PP,OFF");
       ui->pushButtonBilgePump->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");

    }
}

void InstrumentForm::on_pushButtonInteriorLights_released()
{
    if(ui->pushButtonInteriorLights->isChecked())
    {
        writeToSocket(tr(",LED_RED,%1,LED_GREEN,%2,LED_BLUE,%3").arg(mColorDialog->getRed()).arg(mColorDialog->getGreen()).arg(mColorDialog->getBlue()));
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {

        writeToSocket(",LED_RED,0,LED_GREEN,0,LED_BLUE,0");
        ui->pushButtonInteriorLights->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
}

void InstrumentForm::on_pushButtonWindowWiper_released()
{
    if(ui->pushButtonWindowWiper->isChecked())
    {
        writeToSocket(",RELAY_WIPER,ON");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {
        writeToSocket(",RELAY_WIPER,OFF");
        ui->pushButtonWindowWiper->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
}


void InstrumentForm::on_pushButtonHeater_released()
{
    if(ui->pushButtonHeater->isChecked())
    {
        writeToSocket(",HEATER,ON");
        ui->pushButtonHeater->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {
        writeToSocket(",HEATER,OFF");
        ui->pushButtonHeater->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
}

void InstrumentForm::on_pushButtonHorn_pressed()
{
    ui->pushButtonHorn->setText("TUUUUT!!");
    ui->pushButtonHorn->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
}

void InstrumentForm::on_pushButtonHorn_released()
{
    ui->pushButtonHorn->setText("");
    ui->pushButtonHorn->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
}

void InstrumentForm::on_pushButtonInstruments_clicked()
{
    if(ui->pushButtonInstruments->isChecked())
    {
        writeToSocket(",INSTRUMENT,ON");
        ui->pushButtonInstruments->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {
        writeToSocket(",INSTRUMENT,OFF");
        ui->pushButtonInstruments->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
}

void InstrumentForm::on_pushButtonFloodlight_clicked()
{
    if(ui->pushButtonFloodlight->isChecked())
    {
        ui->pushButtonFloodlight->setStyleSheet("QPushButton { background-color: rgb(0, 170, 255); border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
    else
    {
        ui->pushButtonFloodlight->setStyleSheet("QPushButton {border-radius: 100px; border: 10px solid #555; border-color: rgb(0, 170, 255);}");
    }
}
