#include "atttudeindicatorform.h"
#include "ui_atttudeindicatorform.h"

AtttudeIndicatorForm::AtttudeIndicatorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtttudeIndicatorForm)
{
    ui->setupUi(this);

    mAttitudeGauge = new QcGaugeWidget;
    mAttitudeGauge->addBackground(0);
    QcBackgroundItem *bkg = mAttitudeGauge->addBackground(100);
    bkg->clearrColors();
    bkg->addColor(0.1,Qt::black);
    bkg->addColor(1.0,Qt::white);
    mAttMeter = mAttitudeGauge->addAttitudeMeter(150);

    mAttitudeNeedle = mAttitudeGauge->addNeedle(70);
    mAttitudeNeedle->setMinDegree(0);
    mAttitudeNeedle->setMaxDegree(180);
    mAttitudeNeedle->setValueRange(0,180);
    mAttitudeNeedle->setCurrentValue(90);
    mAttitudeNeedle->setColor(Qt::white);
    mAttitudeNeedle->setNeedle(QcNeedleItem::AttitudeMeterNeedle);
    mAttitudeGauge->addGlass(80);
    ui->verticalLayout->addWidget(mAttitudeGauge);
}

AtttudeIndicatorForm::~AtttudeIndicatorForm()
{
    delete ui;
}

void AtttudeIndicatorForm::on_horizontal_valueChanged(int value)
{
    // roll
    mAttitudeNeedle->setCurrentValue(90-value);
    mAttMeter->setCurrentRoll(value);
}

void AtttudeIndicatorForm::on_vertical_valueChanged(int value)
{
    mAttMeter->setCurrentPitch(value);
}

void AtttudeIndicatorForm::sensorData(QString cmd, QString Value)
{
    if(cmd == "ROLL")
    {
       on_horizontal_valueChanged(Value.toFloat());
       ui->labelRoll->setText(tr("Roll: %1").arg(Value));
    }
    else if(cmd == "PITCH")
    {
        on_vertical_valueChanged(Value.toFloat());
        ui->labelPitch->setText(tr("Pitch: %1").arg(Value));
    }
    else
    {
        return;
    }
}
