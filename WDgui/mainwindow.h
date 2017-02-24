#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "Video/videoform.h"
#include "Client/tcpclient.h"
#include "WD_Link/WDlink.h"
#include "RovWidgets/atttudeindicatorform.h"
#include "RovWidgets/compassform.h"

#include "Sensors/sensorsetupdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnection_triggered();


    void on_actionSensor_Setup_triggered();

    void on_actionFont_Color_triggered();

    void on_actionConnect_To_Server_triggered();

    void on_actionAttitude_Indicator_triggered();

    void on_actionCompass_triggered();

    void on_actionVideo_Stream_triggered();

    void on_actionFont_Size_triggered();

    void on_actionTrack_Bar_setting_triggered();

private:
    Ui::MainWindow *ui;

    VideoForm *mVideoStream;

    tcpClient *mTcpClient;

    WDlink *mWDlink;

    SensorSetupDialog *mSensorSetup;

    AtttudeIndicatorForm *mAttitudeIndicator;

    CompassForm *mCompassForm;


};

#endif // MAINWINDOW_H
