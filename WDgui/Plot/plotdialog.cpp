#include "plotdialog.h"
#include "ui_plotdialog.h"

plotDialog::plotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::plotDialog)
{
    ui->setupUi(this);

    ui->checkBox_4->setVisible(false);
    ui->checkBox_5->setVisible(false);
    ui->checkBox_6->setVisible(false);

}

plotDialog::~plotDialog()
{
    delete ui;
}

void plotDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();

}

void plotDialog::on_pushButtonApply_clicked()
{

}

void plotDialog::plotData(QString cmd, QString value)
{



}
