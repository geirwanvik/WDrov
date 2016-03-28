#include "compassform.h"
#include "ui_compassform.h"

CompassForm::CompassForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompassForm)
{
    ui->setupUi(this);

    mCompassGauge = new QcGaugeWidget;

    mCompassGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mCompassGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);

    QcBackgroundItem *bkg2 = mCompassGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::white);
    bkg2->addColor(1.0,Qt::black);

    QcLabelItem *w = mCompassGauge->addLabel(80);
    w->setText("W");
    w->setAngle(0);
    w->setColor(Qt::white);

    QcLabelItem *n = mCompassGauge->addLabel(80);
    n->setText("N");
    n->setAngle(90);
    n->setColor(Qt::red);

    QcLabelItem *e = mCompassGauge->addLabel(80);
    e->setText("E");
    e->setAngle(180);
    e->setColor(Qt::white);

    QcLabelItem *s = mCompassGauge->addLabel(80);
    s->setText("S");
    s->setAngle(270);
    s->setColor(Qt::white);

    QcDegreesItem *deg = mCompassGauge->addDegrees(70);
    deg->setStep(5);
    deg->setMaxDegree(270);
    deg->setMinDegree(-90);
    deg->setColor(Qt::white);
    mCompassNeedle = mCompassGauge->addNeedle(60);
    mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
    mCompassNeedle->setValueRange(0,360);
    mCompassNeedle->setMaxDegree(90);
    mCompassNeedle->setMinDegree(-270);
    mCompassGauge->addBackground(7);
    mCompassGauge->addGlass(88);
    ui->verticalLayout->addWidget(mCompassGauge);
}

CompassForm::~CompassForm()
{
    delete ui;
}

void CompassForm::on_Compass_valueChanged(int value)
{
    mCompassNeedle->setCurrentValue(value);
}

void CompassForm::sensorData(QString cmd, QString Value)
{
    if(cmd == "HEADING")
    {
        float heading = Value.toFloat() + 180;
        on_Compass_valueChanged(heading);
        ui->labelHeading->setText(tr("Heading: %1 Degrees").arg(QString::number(heading)));
       // qDebug() << "Raw value: " << Value.toFloat() << "Added 180deg: " << Value.toFloat() + 180;
    }
    else
    {
        return;
    }
}
