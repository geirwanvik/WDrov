#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   //Read settings
   readSetting();
   //Navigation Toolbar
   createToolbar();
   //The apperacen of the app
   setupApperance();
   //Generel objects
   initObjectAndConnection();



#ifdef Q_OS_ANDROID
  // initAndroidStuff();
#endif

   ui->stackedWidget->setCurrentIndex(0);
   mBoatPanel->setChecked(true);

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
    ui->toolBar->setIconSize(QSize(140*mScreen->ratio(),140*mScreen->ratio()));
    ui->toolBar->setMovable(false);


   // QApplication::setStyle(new styleOne);

    //trying to sett correct font for screen specs
    fontNormalSize.setFamily(fontNormalSize.defaultFamily());
    fontNormalSize.setBold(true);
    fontNormalSize.setPointSize(12 + mScreen->ratioFont());

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
    connect(mBoatStatus, SIGNAL(triggered(bool)), this, SLOT(click_BoatStatus()));

    mBoatNavigation = new QAction(QIcon(":/icons/pictures/Boat icon/Map-512.png"), "Navigation", this);
    mBoatNavigation->setCheckable(true);
    ui->toolBar->addAction(mBoatNavigation);
    connect(mBoatNavigation, SIGNAL(triggered(bool)), this, SLOT(click_Navigation()));

    mBoatMusic = new QAction(QIcon(":/icons/pictures/Boat icon/MusicNote.png"), "Music", this);
    mBoatMusic->setCheckable(true);
    ui->toolBar->addAction(mBoatMusic);
    connect(mBoatMusic, SIGNAL(triggered(bool)), this, SLOT(click_BoatMusic()));


}

void MainWindow::click_BoatInstrument()
{
    //Instrument settings
    ui->stackedWidget->setCurrentIndex(0);
    mBoatPanel->setChecked(true);
    mBoatSensors->setChecked(false);
    mBoatStatus->setChecked(false);
    mBoatNavigation->setChecked(false);
    mBoatMusic->setChecked(false);
}

void MainWindow::click_BoatSensors()
{
    //Sensor overview
    ui->stackedWidget->setCurrentIndex(1);
    mBoatPanel->setChecked(false);
    mBoatSensors->setChecked(true);
    mBoatStatus->setChecked(false);
    mBoatNavigation->setChecked(false);
    mBoatMusic->setChecked(false);
}

void MainWindow::click_BoatStatus()
{
    //Boat sensors
    mBoatPanel->setChecked(false);
    mBoatSensors->setChecked(false);
    mBoatStatus->setChecked(true);
    mBoatNavigation->setChecked(false);
    mBoatMusic->setChecked(false);
}

void MainWindow::click_Navigation()
{
    mBoatPanel->setChecked(false);
    mBoatSensors->setChecked(false);
    mBoatStatus->setChecked(false);
    mBoatNavigation->setChecked(true);
    mBoatMusic->setChecked(false);
}

void MainWindow::click_BoatMusic()
{
    mBoatPanel->setChecked(false);
    mBoatSensors->setChecked(false);
    mBoatStatus->setChecked(false);
    mBoatNavigation->setChecked(false);
    mBoatMusic->setChecked(true);
}

void MainWindow::bluetoothStartConnection()
{
   // mProgressInd->show();
    //mProgressInd->startAnimation();
    ui->statusBar->showMessage("Connecting....");
}

void MainWindow::bluetoothDoneConnection()
{
    mProgressInd->stopAnimation();
    mProgressInd->hide();
}

void MainWindow::bluetoothFailedConnection()
{
    mProgressInd->stopAnimation();
    mProgressInd->hide();
}




void MainWindow::initObjectAndConnection()
{
    mInstrumentForm = new InstrumentForm(this);
    ui->scrollAreaIntrumentForm->setWidget(mInstrumentForm);

    mSensorOverviewForm = new SensorOverviewForm(this);
    ui->scrollAreaSensorOverview->setWidget(mSensorOverviewForm);

    mProgressInd = new QProgressIndicator(this);
    mProgressInd->setStyleSheet("QWidget{background: transparent;");
    mProgressInd->setGeometry(0,0, 250*mScreen->ratio(), 250*mScreen->ratio());
    mProgressInd->move(QApplication::desktop()->screen()->rect().center() - mProgressInd->rect().center());
    mProgressInd->hide();


    mSocket = new bluetooththread(this);
    connect(mSocket, SIGNAL(Doneconnecting()), this, SLOT(bluetoothDoneConnection()));
    connect(mSocket, SIGNAL(DoneDisconnecting()), this, SLOT(bluetoothFailedConnection()));
    connect(mSocket, SIGNAL(failedToConnect()), this, SLOT(bluetoothFailedConnection()));

    mWdLink = new WDlink(this);
    connect(mInstrumentForm, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(sendWdLink(QString)));
    connect(mWdLink, SIGNAL(WDlinkSend(QString&)), mSocket, SLOT(writeString(QString&)));

    if(ui->checkBoxConnectAtStart->isChecked())
    {
       // mSocket->connectToSocketNow();
        //bluetoothStartConnection();
    }
    else
    {
        return;
    }

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
       mSocket->showSetupWindow();
        qDebug() << "Bluetooth selected as commmunication";
    }
    else if(ui->radioButtonTcp->isChecked())
    {
        QMessageBox::information(this, "WD Gui Boat", "No Support for TCP at the moment!");
        qDebug() << "TCP selected as communication";
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

#ifdef Q_OS_ANDROID

void MainWindow::initAndroidStuff()
{
    setScreenAwake();
}

void MainWindow::setScreenAwake()
{
    QAndroidJniObject activity = QtAndroid::androidActivity();
     if (activity.isValid()) {
       QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
       if (window.isValid()) {
         const int FLAG_KEEP_SCREEN_ON = 128;
         const int FLAG_FULLSCREEN = 1024;
         // both flags have to be set
         window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON | FLAG_FULLSCREEN);
         QAndroidJniEnvironment env;
         if (env->ExceptionCheck()) // This part is necessary for Lolipop and above
           env->ExceptionClear();
       }
     }
}
#endif


void MainWindow::on_actionSensor_View_triggered()
{
    mSensorOverviewForm->showSensorConfig();
}
