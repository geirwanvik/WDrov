#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QSettings>
#include <QMessageBox>
#include <QSwipeGesture>
#include <QTimer>
#include <QScroller>
#include <QScrollEvent>

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

#include "hmi/gaugedialog.h"

#include "Android_Sensors/androidsensordialog.h"

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
    void bluetoothStartConnection();
    void bluetoothDoneConnection();
    void bluetoothFailedConnection();
    void on_actionSensor_View_triggered();
    void on_actionSerial_Port_triggered();
    void timerTimeOutScreenSaver();
    void on_actionAll_Sensor_triggered();
    void on_actionCommunication_Debug_triggered();
    void on_actionInterior_Light_Color_triggered();
    void on_pushButtonCommunication_clicked();

#if  defined(Q_OS_ANDROID)


#else

#endif


signals:


private:
    Ui::MainWindow *ui;
    void initObjectAndConnection();
    void readSetting();
    void writeSetting();
    void scrollerSetup();


    WDLink *mWdLink;
    wdParser *mWdParser;

    InstrumentForm *mInstrumentForm;

    SensorOverviewForm *mSensorOverviewForm;

    AllSensorsDialog *mAllSensorOverview;

    //Screen data, set font and sizes
    void setupApperance();
    ScreenData *mScreen;
    QFont fontNormalSize;

    //Progress window when things take time
    QProgressIndicator *mProgressInd;

    bool event(QEvent *event);
    bool gestureEvent(QGestureEvent *event);
    void swipeTriggered(QSwipeGesture *swipe);

    gaugeDialog *mGaugeDialog;

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
