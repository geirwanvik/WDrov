#include "colordialog.h"
#include "ui_colordialog.h"

ColorDialog::ColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else
    this->resize(1000,750);
#endif

    Red = 0;
    Green = 0;
    Blue = 0;

    ReadSetting();

}

ColorDialog::~ColorDialog()
{
    delete ui;
}

void ColorDialog::updateResultColor()
{
    ui->label->setStyleSheet(tr("QLabel { background-color: rgb(%1, %2, %3);border-radius: 11px; border: 2px solid #555; color : white;}").arg(Red).arg(Green).arg(Blue));
    emit writeToSocket(tr(",LED_RED,%1,LED_GREEN,%2,LED_BLUE,%3").arg(Red).arg(Green).arg(Blue));
}

void ColorDialog::updateSliders()
{
    ui->horizontalSliderBlue->setValue(Blue);
    ui->horizontalSliderRed->setValue(Red);
    ui->horizontalSliderGreen->setValue(Green);
}

void ColorDialog::on_horizontalSliderRed_sliderMoved(int position)
{
    Red = position;
    updateResultColor();
}

void ColorDialog::on_horizontalSliderGreen_sliderMoved(int position)
{
    Green = position;
    updateResultColor();
}

void ColorDialog::on_horizontalSliderBlue_sliderMoved(int position)
{
    Blue = position;
    updateResultColor();
}

void ColorDialog::ReadSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatColorDialog");
    Red = settings.value("Red", Red).toUInt();
    Green = settings.value("Green", Green).toUInt();
    Blue = settings.value("Blue", Blue).toInt();
    settings.endGroup();

    updateResultColor();
    updateSliders();
}

void ColorDialog::WriteSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatColorDialog");
    settings.setValue("Red", Red);
    settings.setValue("Green", Green);
    settings.setValue("Blue", Blue);
    settings.endGroup();


}

void ColorDialog::on_pushButtonSaveAndClose_clicked()
{
    WriteSetting();
    this->close();
}

quint8 ColorDialog::getBlue() const
{
    return Blue;
}

void ColorDialog::setBlue(const quint8 &value)
{
    Blue = value;
}

quint8 ColorDialog::getGreen() const
{
    return Green;
}

void ColorDialog::setGreen(const quint8 &value)
{
    Green = value;
}

quint8 ColorDialog::getRed() const
{
    return Red;
}

void ColorDialog::setRed(const quint8 &value)
{
    Red = value;
}

void ColorDialog::on_pushButtonUpdate_clicked()
{
    emit writeToSocket(tr(",LED_RED,%1,LED_GREEN,%2,LED_BLUE,%3").arg(Red).arg(Green).arg(Blue));

}

void ColorDialog::on_pushButtonRed_clicked()
{
    ui->horizontalSliderRed->setValue(255);
    ui->horizontalSliderGreen->setValue(0);
    ui->horizontalSliderBlue->setValue(0);
    Red = 255;
    Green = 0;
    Blue = 0;
    updateResultColor();
}

void ColorDialog::on_pushButtonWhite_clicked()
{
    ui->horizontalSliderRed->setValue(255);
    ui->horizontalSliderGreen->setValue(255);
    ui->horizontalSliderBlue->setValue(255);
    Red = 255;
    Green = 255;
    Blue = 255;
    updateResultColor();
}

void ColorDialog::on_pushButtonPurple_clicked()
{
    ui->horizontalSliderRed->setValue(255);
    ui->horizontalSliderGreen->setValue(0);
    ui->horizontalSliderBlue->setValue(185);
    Red = 255;
    Green = 0;
    Blue = 185;
    updateResultColor();
}
