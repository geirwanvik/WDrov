#include "fontsizedialog.h"
#include "ui_fontsizedialog.h"

FontSizeDialog::FontSizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontSizeDialog)
{
    ui->setupUi(this);

    readSettings();

    ui->lineEditFontSize->setText(QString::number(fontSize));
    ui->lineEditFontBold->setText(QString::number(fontBold));
}

FontSizeDialog::~FontSizeDialog()
{
    delete ui;
}

float FontSizeDialog::getFontSize() const
{
    return fontSize;
}

void FontSizeDialog::setFontSize(float value)
{
    fontSize = value;
}

float FontSizeDialog::getFontBold() const
{
    return fontBold;
}

void FontSizeDialog::setFontBold(float value)
{
    fontBold = value;
}


void FontSizeDialog::writeSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_StreamCore");
    settings.setValue("fontSize", fontSize);
    settings.setValue("fontBold", fontBold);
    settings.endGroup();
}

void FontSizeDialog::readSettings()
{
    QSettings settings("WD Electronics", "WD-ROV");
    settings.beginGroup("WD_StreamCore");
    fontSize = settings.value("fontSize", fontSize).toFloat();
    fontBold = settings.value("fontBold", fontBold).toFloat();
    settings.endGroup();
}

void FontSizeDialog::on_pushButtonSaveAndClose_clicked()
{
    setFontSize(ui->lineEditFontSize->text().toFloat());
    setFontBold(ui->lineEditFontBold->text().toFloat());

    writeSettings();
    emit fontChanged(getFontSize(), getFontBold());

    this->hide();

}

void FontSizeDialog::on_pushButtonCancel_clicked()
{
    this->hide();

}
