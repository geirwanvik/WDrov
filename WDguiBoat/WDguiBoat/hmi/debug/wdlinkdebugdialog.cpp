#include "wdlinkdebugdialog.h"
#include "ui_wdlinkdebugdialog.h"

wdLinkDebugDialog::wdLinkDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wdLinkDebugDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else

#endif

    QScroller *scroller = QScroller::scroller(ui->textBrowser);
    scroller->grabGesture(ui->textBrowser, QScroller::LeftMouseButtonGesture);
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

void wdLinkDebugDialog::wdlinkRaw(QString string)
{
    if(ui->checkBoxStopPrint->isChecked())
    {
        return;
    }
    else
    {
        ui->textBrowser->append(string);
    }
}

void wdLinkDebugDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}

void wdLinkDebugDialog::on_pushButtonSend_clicked()
{
    QString sendData;

    sendData.append("ARDU,");
    sendData.append(ui->lineEditNewMessage->text().toUpper());

    emit writeToSocket(sendData);

    sendData.clear();
}
