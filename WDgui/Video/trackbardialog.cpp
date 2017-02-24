#include "trackbardialog.h"
#include "ui_trackbardialog.h"

trackBarDialog::trackBarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trackBarDialog)
{
    ui->setupUi(this);
}

trackBarDialog::~trackBarDialog()
{
    delete ui;
}

void trackBarDialog::on_horizontalSliderH_Min_valueChanged(int value)
{
    ui->groupBoxH_Min->setTitle(tr("H Min: %1").arg(QString::number(value)));
    H_MIN = value;
}

void trackBarDialog::on_horizontalSliderH_Max_valueChanged(int value)
{
    ui->groupBoxH_Max->setTitle(tr("H Max: %1").arg(QString::number(value)));
    H_MAX = value;
}

void trackBarDialog::on_horizontalSliderS_Min_valueChanged(int value)
{
    ui->groupBoxS_Min->setTitle(tr("S Min: %1").arg(value));
    S_MIN = value;
}

void trackBarDialog::on_horizontalSliderS_Max_valueChanged(int value)
{
    ui->groupBoxS_Max->setTitle(tr("S Max: %1").arg(value));
    S_MAX = value;
}

void trackBarDialog::on_horizontalSliderV_Min_valueChanged(int value)
{
    ui->groupBoxV_Min->setTitle(tr("V Min: %1").arg(value));
    V_MIN = value;
}

void trackBarDialog::on_horizontalSliderV_Max_valueChanged(int value)
{
    ui->groupBoxv_Max->setTitle(tr("V Max: %1").arg(value));
    V_MAX = value;
}

void trackBarDialog::on_pushButtonOk_clicked()
{
    this->hide();
}

void trackBarDialog::on_pushButtonCancel_clicked()
{
    this->hide();
}
