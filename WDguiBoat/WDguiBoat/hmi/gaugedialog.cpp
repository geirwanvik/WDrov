#include "gaugedialog.h"
#include "ui_gaugedialog.h"

gaugeDialog::gaugeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gaugeDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else
    this->resize(1000,750);
#endif

  apperanceSetup();


}

gaugeDialog::~gaugeDialog()
{
    delete ui;
}

void gaugeDialog::apperanceSetup()
{

    ui->progressKnots->setRange(0, 50);
    ui->progressKnots->setNullPosition(QRoundProgressBar::PositionBottom);
    QString knots = QString( "%1 Kn" ).arg(15.5);
    ui->progressKnots->setFormat(knots);

    ui->progressVolt->setRange(0, 20);
    ui->progressVolt->setNullPosition(QRoundProgressBar::PositionBottom);
    QString Volts = QString("%1 V").arg(12.4);
    ui->progressVolt->setFormat(Volts);
    ui->progressVolt->setValue(12.4);

    ui->ProgressCurrent->setRange(0, 10);
    ui->ProgressCurrent->setNullPosition(QRoundProgressBar::PositionBottom);
    QString current = QString("%1 A").arg(1.03);
    ui->ProgressCurrent->setFormat(current);
    ui->ProgressCurrent->setValue(1.03);

    ui->processGroundCourse->setRange(0, 10);
    ui->processGroundCourse->setNullPosition(QRoundProgressBar::PositionBottom);
    QString heading = QString("%1 Deg").arg(120.2);
    ui->processGroundCourse->setFormat(heading);
    ui->processGroundCourse->setValue(10);

    mCompassGauge = new QcGaugeWidget(this);

       mCompassGauge->addBackground(0);
       QcBackgroundItem *bkg1 = mCompassGauge->addBackground(90);
       bkg1->clearrColors();
       bkg1->addColor(0.1,Qt::darkGray);
       bkg1->addColor(1.0,Qt::white);

       QcBackgroundItem *bkg2 = mCompassGauge->addBackground(50);
       bkg2->clearrColors();
       bkg2->addColor(0.1,Qt::white);
       bkg2->addColor(1.0,Qt::white);

       QcLabelItem *w = mCompassGauge->addLabel(80);
       w->setText("W");
       w->setAngle(0);
       w->setColor(Qt::black);

       QcLabelItem *n = mCompassGauge->addLabel(80);
       n->setText("N");
       n->setAngle(90);
       n->setColor(Qt::red);

       QcLabelItem *e = mCompassGauge->addLabel(80);
       e->setText("E");
       e->setAngle(180);
       e->setColor(Qt::black);

       QcLabelItem *s = mCompassGauge->addLabel(80);
       s->setText("S");
       s->setAngle(270);
       s->setColor(Qt::black);

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
       ui->compassWidget2->addWidget(mCompassGauge);

}

void gaugeDialog::gpsData(QString command, QString value)
{

    if(command == CommandString[GPS_GROUND_SPEED_KNOTS])
    {
       QString knots = QString( "%1 Kn" ).arg(value.toDouble());
       ui->progressKnots->setFormat(knots);
       ui->progressKnots->setValue(value.toDouble());
    }
    else if(command == CommandString[GPS_GROUND_COURSE])
    {
        QString heading = QString("%1 Deg").arg(value.toDouble());
        ui->processGroundCourse->setFormat(heading);
        ui->processGroundCourse->setValue(value.toDouble());
    }
    else
    {
        return;
    }
}

void gaugeDialog::dht22Data(QString command, QString value)
{
    if(command == CommandString[VOLTAGE])
    {
        QString Volts = QString("%1 V").arg(value.toDouble());
        ui->progressVolt->setFormat(Volts);
        ui->progressVolt->setValue(value.toDouble());
    }
    else if(command == CommandString[CURRENT])
    {
        QString current = QString("%1 A").arg(value.toDouble());
        ui->ProgressCurrent->setFormat(current);
        ui->ProgressCurrent->setValue(value.toDouble());
    }
    else
    {
        return;
    }
}

void gaugeDialog::imuData(QString command, QString value)
{
    if(command == CommandString[IMU_HEADING])
    {
        double heading = value.toDouble() + 180;
        mCompassNeedle->setCurrentValue(heading);
    }
    else
    {
        return;
    }
}
