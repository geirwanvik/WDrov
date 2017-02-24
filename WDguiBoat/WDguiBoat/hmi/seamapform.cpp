#include "seamapform.h"
#include "ui_seamapform.h"

SeaMapForm::SeaMapForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeaMapForm)
{
    ui->setupUi(this);




}

SeaMapForm::~SeaMapForm()
{
    delete ui;
}
