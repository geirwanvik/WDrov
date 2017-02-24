#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_actionSensor_View_triggered()
{
    mSensorOverviewForm->showSensorConfig();
}

void MainWindow::on_actionSerial_Port_triggered()
{
#if  defined(Q_OS_ANDROID)


#else
    ShowSetupSerial();
#endif
}


void MainWindow::on_actionAll_Sensor_triggered()
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

void MainWindow::on_actionCommunication_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionCommunication_Debug_triggered()
{
    wdLinkDebugDialog *mWdlinkDebug = new wdLinkDebugDialog(this);

    connect(mWdParser, SIGNAL(Dht22Data(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdParser, SIGNAL(GpsData(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdParser, SIGNAL(ImuData(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdParser, SIGNAL(instrumentData(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdParser, SIGNAL(LedFeedback(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdParser, SIGNAL(buttonPanelFeedback(QString,QString)), mWdlinkDebug, SLOT(wdLinkData(QString,QString)));
    connect(mWdlinkDebug, SIGNAL(writeToSocket(QString)), mWdLink, SLOT(Send(QString)));
    connect(mWdLink, SIGNAL(freshData(QString)), mWdlinkDebug, SLOT(wdlinkRaw(QString)));


    mWdlinkDebug->setModal(true);
    mWdlinkDebug->show();
}
void MainWindow::on_actionInterior_Light_Color_triggered()
{
      mInstrumentForm->showColorDialog();
}
