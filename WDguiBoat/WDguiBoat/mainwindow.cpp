#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   //Navigation Toolbar
   createToolbar();
   //Generel objects
   initObjectAndConnection();
   //Read settings
   readSetting();

   //The apperacen off the app
   setupApperance();

   ui->statusBar->showMessage("Welcomme To WD Boat!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupApperance()
{
    mScreen = new ScreenData(this);

    //We try to size toolbar for screen size
    ui->toolBar->setIconSize(QSize(100*mScreen->ratio(),100*mScreen->ratio()));
    ui->toolBar->setMovable(false);


    //QApplication::setStyle(new styleOne);

    //trying to sett correct font for screen specs
    fontNormalSize.setFamily(fontNormalSize.defaultFamily());
    fontNormalSize.setBold(true);
    fontNormalSize.setPointSize(14 + mScreen->ratioFont());

    QApplication::setFont(fontNormalSize);







}

void MainWindow::createToolbar()
{
    mBoatPanel = new QAction(QIcon(":/icons/pictures/Boat icon/motor-boat-512.png"), "Instrument", this);
    mBoatPanel->setCheckable(true);
    ui->toolBar->addAction(mBoatPanel);
    connect(mBoatPanel, SIGNAL(triggered(bool)), this, SLOT(click_BoatInstrument()));


    mBoatSensors = new QAction(QIcon(":/icons/pictures/Boat icon/compass.png"), "Sensors", this);
    mBoatSensors->setCheckable(true);
    ui->toolBar->addAction(mBoatSensors);
    connect(mBoatSensors, SIGNAL(triggered(bool)), this, SLOT(click_BoatSensors()));

    mBoatStatus = new QAction(QIcon(":/icons/pictures/Boat icon/boat_propeller.png"), "Motor", this);
    mBoatStatus->setCheckable(true);
    ui->toolBar->addAction(mBoatStatus);

    mBoatMusic = new QAction(QIcon(":/icons/pictures/Boat icon/MusicNote.png"), "Music", this);
    mBoatMusic->setCheckable(true);
    ui->toolBar->addAction(mBoatMusic);


}

void MainWindow::initObjectAndConnection()
{
    mInstrumentForm = new InstrumentForm(this);
    ui->scrollAreaIntrumentForm->setWidget(mInstrumentForm);

    mSensorOverviewForm = new SensorOverviewForm(this);
    ui->scrollAreaSensorOverview->setWidget(mSensorOverviewForm);
}

void MainWindow::readSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatMainwindow");
    ui->radioButtonBluetooth->setChecked(settings.value("BluetoothRadioButton", ui->radioButtonBluetooth->isChecked()).toBool());
   ui->radioButtonTcp->setChecked(settings.value("TcpRadioButton", ui->radioButtonTcp->isChecked()).toBool());
    ui->checkBoxConnectAtStart->setChecked(settings.value("ConnectAtStart", ui->checkBoxConnectAtStart->isChecked()).toBool());
   // firsTimeSetup = settings.value("FirstTimeSetup", firsTimeSetup).toBool();
    settings.endGroup();
}

void MainWindow::writeSetting()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("WDBoatMainwindow");
    settings.setValue("BluetoothRadioButton", ui->radioButtonBluetooth->isChecked());
    settings.setValue("TcpRadioButton", ui->radioButtonTcp->isChecked());
    settings.setValue("ConnectAtStart", ui->checkBoxConnectAtStart->isChecked());
   // settings.setValue("FirstTimeSetup", firsTimeSetup);
    settings.endGroup();
}

void MainWindow::on_actionCommunication_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButtonSetupCommunication_clicked()
{
    if(ui->radioButtonBluetooth->isChecked())
    {
        //Bluetooth
        qDebug() << "Bluetooth";
    }
    else if(ui->radioButtonTcp->isChecked())
    {
        qDebug() << "TCP";
    }
    else
    {
        QMessageBox::information(this, "WD Boat", "No Communication was selected!");
        return;
    }
}

void MainWindow::on_pushButtonSaveAndReturn_clicked()
{
    writeSetting();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::click_BoatInstrument()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::click_BoatSensors()
{
    ui->stackedWidget->setCurrentIndex(1);
}


