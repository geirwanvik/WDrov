#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   ui->checkBoxConnectAtStart->setChecked(true);
   ui->radioButtonBluetooth->setChecked(true);
   //Read settings
   readSetting();
   //Navigation Toolbar
   createToolbar();
   //The apperacen of the app
   setupApperance();
   //Generel objects
   initObjectAndConnection();


   ui->stackedWidget->setCurrentIndex(0);
   mBoatPanel->setChecked(true);

   ui->statusBar->showMessage("WD Boat!");

   this->setAttribute(Qt::WA_AcceptTouchEvents);
   this->grabGesture(Qt::SwipeGesture);
   this->setAttribute(Qt::WA_TouchPadAcceptSingleTouchEvents);

   ui->actionAll_Sensor->setVisible(false);


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
    //trying to sett correct font for screen specs
    fontNormalSize.setFamily(fontNormalSize.defaultFamily());
    fontNormalSize.setBold(true);
    fontNormalSize.setPointSize(12 + mScreen->ratioFont());
    QApplication::setFont(fontNormalSize);

}

bool MainWindow::event(QEvent *event)
{


    //QTimer::singleShot(15000,this,SLOT(timerTimeOutScreenSaver()));
    if(event->type() == QEvent::MouseMove || QEvent::MouseButtonPress)
    {
         qDebug() << "Event big time!";
    }

    if (event->type() == QEvent::Gesture)
           return gestureEvent(static_cast<QGestureEvent*>(event));
       return QWidget::event(event);
}

void MainWindow::timerTimeOutScreenSaver()
{
    qDebug() << "Timer overflow!" << mGaugeDialog->isVisible();

    if(mGaugeDialog->isVisible() == false)
    {
        mGaugeDialog->setModal(true);
        mGaugeDialog->show();
    }
    else
    {
        return;
    }
}

bool MainWindow::gestureEvent(QGestureEvent *event)
{

    if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
    {
           swipeTriggered(static_cast<QSwipeGesture *>(swipe));
    }


    return true;

}

void MainWindow::swipeTriggered(QSwipeGesture *swipe)
{
    if (swipe->state() == Qt::GestureFinished) {
           if (swipe->horizontalDirection() == QSwipeGesture::Left
               || swipe->verticalDirection() == QSwipeGesture::Up) {
               qDebug() << "swipeTriggered(): swipe to previous";
               mGaugeDialog->rightPageAnimation();
               mGaugeDialog->setModal(true);
               mGaugeDialog->show();

           } else {
               qDebug() << "swipeTriggered(): swipe to next";
                AndroidSensorDialog *mAndroidSensors = new AndroidSensorDialog(this);
                mAndroidSensors->setModal(true);
                mAndroidSensors->show();
           }
           update();
       }
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
    //ui->toolBar->addAction(mBoatStatus);
    connect(mBoatStatus, SIGNAL(triggered(bool)), this, SLOT(click_BoatStatus()));

    mBoatNavigation = new QAction(QIcon(":/icons/pictures/Boat icon/Map-512.png"), "Navigation", this);
    mBoatNavigation->setCheckable(true);
   // ui->toolBar->addAction(mBoatNavigation);
    connect(mBoatNavigation, SIGNAL(triggered(bool)), this, SLOT(click_Navigation()));

    mBoatMusic = new QAction(QIcon(":/icons/pictures/Boat icon/MusicNote.png"), "Music", this);
    mBoatMusic->setCheckable(true);
   // ui->toolBar->addAction(mBoatMusic);
    connect(mBoatMusic, SIGNAL(triggered(bool)), this, SLOT(click_BoatMusic()));

    mRawSensorData = new QAction(QIcon(":/icons/pictures/Instrument/RawSensor.png"), "Raw Sensors", this);
    mBoatMusic->setCheckable(true);
    ui->toolBar->addAction(mRawSensorData);
    connect(mRawSensorData, SIGNAL(triggered(bool)), this, SLOT(click_RawSensorData()));

    mSettings = new QAction(QIcon(":/icon/pictures/Icons/settingSVG.png"), "Settings", this);
    //ui->toolBar->addAction(mSettings);
    connect(mSettings, SIGNAL(triggered(bool)), this, SLOT(click_Settings()));

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

void MainWindow::click_Settings()
{

}

void MainWindow::click_RawSensorData()
{

    mAllSensorOverview = new AllSensorsDialog(this);
    connect(mWdParser, SIGNAL(Dht22Data(QString,QString)), mAllSensorOverview, SLOT(sensorData(QString,QString)));
    connect(mWdParser, SIGNAL(GpsData(QString,QString)), mAllSensorOverview, SLOT(sensorData(QString,QString)));
    connect(mWdParser, SIGNAL(ImuData(QString,QString)), mAllSensorOverview, SLOT(sensorData(QString,QString)));
    connect(mWdParser, SIGNAL(PowerData(QString,QString)), mAllSensorOverview, SLOT(sensorData(QString,QString)));
    connect(mWdParser, SIGNAL(LedFeedback(QString,QString)), mAllSensorOverview, SLOT(sensorData(QString,QString)));
    connect(mAllSensorOverview, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(Send(QString)));
    mAllSensorOverview->setModal(true);
    mAllSensorOverview->show();

}

void MainWindow::bluetoothStartConnection()
{
    mProgressInd->show();
    mProgressInd->startAnimation();
    ui->statusBar->showMessage("Connecting....");
    ui->statusBar->setStyleSheet("QStatusBar{background:rgba(255, 255, 127)}");
    mInstrumentForm->connectedToWdCore(true);

}

void MainWindow::bluetoothDoneConnection()
{
    mProgressInd->stopAnimation();
    mProgressInd->hide();
    ui->statusBar->showMessage("Bluetooth Connected!");
    ui->statusBar->setStyleSheet("QStatusBar{background:rgba(0, 255, 0, 255)}");
}

void MainWindow::bluetoothFailedConnection()
{
    mProgressInd->stopAnimation();
    mProgressInd->hide();
    ui->statusBar->showMessage("Disconncted!");
    ui->statusBar->setStyleSheet("QStatusBar{background:rgba(255, 0, 0, 255)}");
    mInstrumentForm->connectedToWdCore(false);
   // ui->toolBar->setEnabled(false);
   // ui->stackedWidget->setCurrentIndex(4);
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

    mWdLink = new WDLink(this);

    mWdParser = new wdParser(this);
    connect(mWdLink, SIGNAL(freshData(QString)), mWdParser, SLOT(dataForParsing(QString)));

#ifdef Q_OS_ANDROID
   ui->actionSerial_Port->setVisible(false);
   initAndroidStuff();
   mSocket = new bluetooththread(this);
   connect(mSocket, SIGNAL(Doneconnecting()), this, SLOT(bluetoothDoneConnection()));
   connect(mSocket, SIGNAL(DoneDisconnecting()), this, SLOT(bluetoothFailedConnection()));
   connect(mSocket, SIGNAL(failedToConnect()), this, SLOT(bluetoothFailedConnection()));
   connect(mSocket, SIGNAL(startConnecting()), this, SLOT(bluetoothStartConnection()));
   connect(mInstrumentForm, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(Send(QString)));
   connect(mWdLink, SIGNAL(sendByteArrayToSocket(QByteArray)), mSocket, SLOT(writeBytes(QByteArray)));
   connect(mSocket, SIGNAL(readyRead(QByteArray)), mWdLink, SLOT(Receive(QByteArray)));  
#else
   mSocket = new serialPort(this);
   connect(mInstrumentForm, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(Send(QString)));
   connect(mSocket, SIGNAL(readyRead(QByteArray)), mWdLink, SLOT(Receive(QByteArray)));
   connect(mWdLink, SIGNAL(sendByteArrayToSocket(QByteArray)), mSocket, SLOT(writeBytes(QByteArray)));
   this->resize(1300, 800);
#endif

   mGaugeDialog = new gaugeDialog(this);
   connect(mWdParser, SIGNAL(GpsData(QString,QString)), mGaugeDialog, SLOT(gpsData(QString,QString)));
   connect(mWdParser, SIGNAL(Dht22Data(QString,QString)), mGaugeDialog, SLOT(dht22Data(QString,QString)));
   connect(mWdParser, SIGNAL(ImuData(QString,QString)), mGaugeDialog, SLOT(imuData(QString,QString)));


    connect(mWdParser, SIGNAL(ImuData(QString,QString)), mSensorOverviewForm, SLOT(imuData(QString,QString)));
    connect(mWdParser, SIGNAL(PowerData(QString,QString)), mSensorOverviewForm, SLOT(powerData(QString,QString)));
    connect(mWdParser, SIGNAL(Dht22Data(QString,QString)), mSensorOverviewForm, SLOT(dht22Data(QString,QString)));
    connect(mWdParser, SIGNAL(GpsData(QString,QString)), mSensorOverviewForm, SLOT(gpsData(QString,QString)));

    connect(mWdParser, SIGNAL(instrumentData(QString,QString)), mInstrumentForm, SLOT(dataFromWdCore(QString,QString)));
    connect(mInstrumentForm->mColorDialog, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(Send(QString)));



    if(ui->checkBoxConnectAtStart->isChecked())
    {
       mSocket->connectToSocketNow();
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

#else



void MainWindow::ShowSetupSerial()
{
    mSocket->showSetupWindow();
}

#endif




