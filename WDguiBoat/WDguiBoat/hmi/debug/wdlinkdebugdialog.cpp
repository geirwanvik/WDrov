#include "wdlinkdebugdialog.h"
#include "ui_wdlinkdebugdialog.h"

wdLinkDebugDialog::wdLinkDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wdLinkDebugDialog)
{
    ui->setupUi(this);
}

wdLinkDebugDialog::~wdLinkDebugDialog()
{
    delete ui;
}

void wdLinkDebugDialog::wdLinkData(QString command, QString value)
{

    if(ui->checkBoxStopPrint->isChecked())
    {
        return;
    }
    else
    {
        ui->textBrowser->append(command + ": " + value);
    }
}

void wdLinkDebugDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}
