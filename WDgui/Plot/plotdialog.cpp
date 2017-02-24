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

    if(cmd.contains("ROLL") && ui->checkBoxRoll->isChecked())
    {
       ui->plotWidget->addGraph(); //Blue
       ui->plotWidget->graph(0)->setPen(QPen(Qt::blue));
       ui->plotWidget->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
       ui->plotWidget->graph(0)->setAntialiasedFill(false);


    }
    else if(cmd.contains("PITCH") && ui->checkBoxPitch->isChecked())
    {

    }
    else if (cmd.contains("HEADING") && ui->checkBoxHeading->isChecked())
    {

    }
    else
    {
        return;
    }


    ui->plotWidget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->plotWidget->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->plotWidget->xAxis->setAutoTickStep(false);
    ui->plotWidget->xAxis->setTickStep(2);
    ui->plotWidget->axisRect()->setupFullAxesBox();

    connect(ui->plotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->yAxis2, SLOT(setRange(QCPRange)));


}
