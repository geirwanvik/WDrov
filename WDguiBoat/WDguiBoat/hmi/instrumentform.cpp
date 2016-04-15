#include "instrumentform.h"
#include "ui_instrumentform.h"

InstrumentForm::InstrumentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstrumentForm)
{
    ui->setupUi(this);

    ui->pushButtonBilgePump->setIcon(QIcon(":/instrumentIcons/pictures/Instrument/bilge pump.png"));
    ui->pushButtonBilgePump->setIconSize(QSize(100,100));
    ui->pushButtonBilgePump->setCheckable(true);

}

InstrumentForm::~InstrumentForm()
{
    delete ui;
}
