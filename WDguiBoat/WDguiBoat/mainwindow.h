#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QSettings>
#include <QMessageBox>

#include "Screen/screendata.h"
#include "Palette/styleone.h"
#include "hmi/instrumentform.h"
#include "Communication/Bluetooth/bluetooththread.h"
#include "wdLink/wdlink.h"
#include "wdLink/wdparser.h"
#include "hmi/sensoroverviewform.h"
#include "progressBar/QProgressIndicator.h"
#include "hmi/allsensorsdialog.h"
#include "hmi/debug/wdlinkdebugdialog.h"

#include "Android_Sensors/androidgps.h"
#include "Android_Sensors/androidaccelerometer.h"
#include "Android_Sensors/androidcompass.h"

#if  defined(Q_OS_ANDROID)
#include <QtAndroidExtras>
#else
#include "Communication/Serial/serialport.h"

#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void on_actionCommunication_triggered();
    void on_pushButtonSetupCommunication_clicked();
    void on_pushButtonSaveAndReturn_clicked();
    void click_BoatInstrument();
    void click_BoatSensors();
    void click_BoatStatus();
    void click_Navigation();
    void click_BoatMusic();
    void click_Settings();
    void click_RawSensorData();
    void bluetoothStartConnection();
    void bluetoothDoneConnection();
    void bluetoothFailedConnection();
    void on_actionSensor_View_triggered();
    void on_actionSerial_Port_triggered();

#if  defined(Q_OS_ANDROID)


#else

#endif

    void on_actionAll_Sensor_triggered();
    void on_actionCommunication_Debug_triggered();

signals:


private:
    Ui::MainWindow *ui;
    void createToolbar();
    void initObjectAndConnection();
    void readSetting();
    void writeSetting();

    //Toolbar button and actions
    QAction *mBoatPanel;
    QAction *mBoatSensors;
    QAction *mBoatStatus;
    QAction *mBoatMusic;
    QAction *mBoatNavigation;
    QAction *mRawSensorData;
    QAction *mSettings;

    WDLink *mWdLink;
    wdParser *mWdParser;

    InstrumentForm *mInstrumentForm;

    SensorOverviewForm *mSensorOverviewForm;

    AllSensorsDialog *mAllSensorOverview;

    androidGps *mAndroidGpsSource;

    androidAccelerometer *mAndroidAccelerometer;

    androidCompass *mCompass;

    //Screen data, set font and sizes
    void setupApperance();
    ScreenData *mScreen;
    QFont fontNormalSize;

    //Progress window when things take time
    QProgressIndicator *mProgressInd;

#if  defined(Q_OS_ANDROID)
    bluetooththread *mSocket;
    void initAndroidStuff();
    void setScreenAwake();

#else
    serialPort *mSocket;
    void ShowSetupSerial();
#endif


};

#endif // MAINWINDOW_H
