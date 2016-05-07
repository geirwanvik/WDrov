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
#include "hmi/sensoroverviewform.h"
#include "WD_Link/WDlink.h"
#include "progressBar/QProgressIndicator.h"

#if  defined(Q_OS_ANDROID)
#include <QtAndroidExtras>
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
    void bluetoothStartConnection();
    void bluetoothDoneConnection();
    void bluetoothFailedConnection();

    void on_actionSensor_View_triggered();

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

    InstrumentForm *mInstrumentForm;

    SensorOverviewForm *mSensorOverviewForm;

    //Screen data, set font and sizes
    void setupApperance();
    ScreenData *mScreen;
    QFont fontNormalSize;

    bluetooththread *mSocket;

    WDlink *mWdLink;

    //Progress window when things take time
    QProgressIndicator *mProgressInd;

#if  defined(Q_OS_ANDROID)
    void initAndroidStuff();
    void setScreenAwake();

#endif


};

#endif // MAINWINDOW_H
