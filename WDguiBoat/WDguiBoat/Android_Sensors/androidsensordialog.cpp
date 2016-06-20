#include "androidsensordialog.h"
#include "ui_androidsensordialog.h"

AndroidSensorDialog::AndroidSensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AndroidSensorDialog)
{
    ui->setupUi(this);
#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else
    this->resize(1000,750);
#endif
}

AndroidSensorDialog::~AndroidSensorDialog()
{
    delete ui;
}

void AndroidSensorDialog::on_pushButtonClose_clicked()
{
    this->hide();
    this->deleteLater();
}
