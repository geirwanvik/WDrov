#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    mVideoStream = new VideoForm(this);
    ui->scrollAreaVideoStream->setWidget(mVideoStream);

    mTcpClient = new tcpClient(this);

    mWDlink = new WDlink(this);

    connect(mTcpClient, SIGNAL(newDataRx(QString&)), mWDlink, SLOT(NewMessage(QString&)));
    connect(mWDlink, SIGNAL(WDlinkSend(QString&)), mTcpClient, SLOT(writeString(QString&)));

    mSensorSetup = new SensorSetupDialog(this);
    connect(mTcpClient, SIGNAL(clientConnected(bool)), mSensorSetup, SLOT(connectedToHost(bool)));

    connect(mSensorSetup, SIGNAL(requestSensorData(QString)), mWDlink, SLOT(sendWdLink(QString)));
    connect(mWDlink, SIGNAL(GetMessageItem(QString,QString)), mVideoStream, SLOT(sensorData(QString,QString)));

    mAttitudeIndicator = new AtttudeIndicatorForm(this);
    ui->scrollAreaAttitude->setWidget(mAttitudeIndicator);
    connect(mWDlink, SIGNAL(GetMessageItem(QString,QString)), mAttitudeIndicator, SLOT(sensorData(QString,QString)));

    mCompassForm = new CompassForm(this);
    ui->scrollAreaCompass->setWidget(mCompassForm);
    connect(mWDlink, SIGNAL(GetMessageItem(QString,QString)), mCompassForm, SLOT(sensorData(QString,QString)));

    QApplication::setStyle(new styleOne);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnection_triggered()
{
    mTcpClient->showClientSetupDialog();
}


void MainWindow::on_actionSensor_Setup_triggered()
{
    mSensorSetup->setModal(true);
    mSensorSetup->show();
}

void MainWindow::on_actionFont_Color_triggered()
{
    mVideoStream->showColorDialog();
}

void MainWindow::on_actionConnect_To_Server_triggered()
{
    mTcpClient->connectToHost();
}

void MainWindow::on_actionAttitude_Indicator_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionCompass_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionVideo_Stream_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionFont_Size_triggered()
{
    mVideoStream->showFontDialog();
}
