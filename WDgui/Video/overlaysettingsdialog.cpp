#include "overlaysettingsdialog.h"
#include "ui_overlaysettingsdialog.h"

OverlaySettingsDialog::OverlaySettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverlaySettingsDialog)
{
    ui->setupUi(this);
}

OverlaySettingsDialog::~OverlaySettingsDialog()
{
    delete ui;
}
