#include "sensorconfigdialog.h"
#include "ui_sensorconfigdialog.h"

SensorConfigDialog::SensorConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SensorConfigDialog)
{
    ui->setupUi(this);

#ifdef Q_OS_ANDROID
    this->setWindowState(Qt::WindowMaximized);
#else

#endif
    readSetting();

    groupRadioButtons();
}

SensorConfigDialog::~SensorConfigDialog()
{
    delete ui;
}

void SensorConfigDialog::on_pushButtonSaveAndClose_clicked()
{
    writeSetting();
    this->hide();
}

void SensorConfigDialog::readSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatScaleConfig");
    ui->radioButtonBatteryV->setChecked(settings.value("radioBatteryV", ui->radioButtonBatteryV->isChecked()).toBool());
    ui->radioButtonGpsSpeed->setChecked(settings.value("radioGpsSpeed", ui->radioButtonGpsSpeed->isChecked()).toBool());
    ui->radioButtonHumidity->setChecked(settings.value("radioHumidity", ui->radioButtonHumidity->isChecked()).toBool());
    ui->radioButtonPitch->setChecked(settings.value("radioPitch", ui->radioButtonPitch->isChecked()).toBool());
    ui->radioButtonRoll->setChecked(settings.value("radioRoll", ui->radioButtonRoll->isChecked()).toBool());
    ui->radioButtonSystemA->setChecked(settings.value("radioSystemA", ui->radioButtonSystemA->isChecked()).toBool());
    ui->radioButtonSystemV->setChecked(settings.value("radioSystemV", ui->radioButtonSystemV->isChecked()).toBool());
    ui->radioButtonTemperature->setChecked(settings.value("Temperature", ui->radioButtonTemperature->isChecked()).toBool());
    ui->radioButtonWaterTemp->setChecked(settings.value("radioWaterTemp", ui->radioButtonWaterTemp->isChecked()).toBool());
    ui->checkBoxFirstVisible->setChecked(settings.value("checkFirst", ui->checkBoxFirstVisible->isChecked()).toBool());
    ui->checkBoxSecondVisible->setChecked(settings.value("checkSecond", ui->checkBoxSecondVisible->isChecked()).toBool());
    ui->checkBoxThirdVisible->setChecked(settings.value("checkThird", ui->checkBoxThirdVisible->isChecked()).toBool());
    ui->checkBoxFourtVisible->setChecked(settings.value("checkFourth", ui->checkBoxFourtVisible->isChecked()).toBool());
    settings.endGroup();
}

void SensorConfigDialog::writeSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatScaleConfig");
    settings.setValue("radioBatteryV", ui->radioButtonBatteryV->isChecked());
    settings.setValue("radioGpsSpeed", ui->radioButtonGpsSpeed->isChecked());
    settings.setValue("radioHumidity", ui->radioButtonHumidity->isChecked());
    settings.setValue("radioPitch", ui->radioButtonPitch->isChecked());
    settings.setValue("radioRoll", ui->radioButtonRoll->isChecked());
    settings.setValue("radioSystemA", ui->radioButtonSystemA->isChecked());
    settings.setValue("radioSystemV", ui->radioButtonSystemV->isChecked());
    settings.setValue("Temperature", ui->radioButtonTemperature->isChecked());
    settings.setValue("radioWaterTemp", ui->radioButtonWaterTemp->isChecked());
    settings.setValue("checkFirst", ui->checkBoxFirstVisible->isChecked());
    settings.setValue("checkSecond", ui->checkBoxSecondVisible->isChecked());
    settings.setValue("checkThird", ui->checkBoxThirdVisible->isChecked());
    settings.setValue("checkFourth", ui->checkBoxFourtVisible->isChecked());
    settings.endGroup();
}

void SensorConfigDialog::groupRadioButtons()
{

    QList<QRadioButton *> firstGroup = ui->groupBoxFirst->findChildren<QRadioButton *>();
    for(int i = 0; i < firstGroup.size(); ++i)
    {
        firstButtonGroup.addButton(firstGroup[i],i);
    }


    QList<QRadioButton *> secondGroup = ui->groupBoxSecond->findChildren<QRadioButton *>();
    for(int i = 0; i < secondGroup.size(); ++i)
    {
        secondButtonGroup.addButton(secondGroup[i],i);
    }


    QList<QRadioButton *> thirdGroup = ui->groupBoxThird->findChildren<QRadioButton *>();
    for(int i = 0; i < thirdGroup.size(); ++i)
    {
        thirdButtonGroup.addButton(thirdGroup[i],i);
    }

    QList<QRadioButton *> fourthGroup = ui->groupBoxFourth->findChildren<QRadioButton *>();
    for(int i = 0; i < fourthGroup.size(); ++i)
    {
        fourthButtonGroup.addButton(fourthGroup[i],i);
    }

}

