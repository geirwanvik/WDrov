#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QApplication::setStyle(new styleOne);

   createToolbar();

    ui->toolBar->setIconSize(QSize(80,80));

    mInstrumentForm = new InstrumentForm(this);
    ui->scrollAreaIntrumentForm->setWidget(mInstrumentForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolbar()
{
    mBoatPanel = new QAction(QIcon(":/icons/pictures/Boat icon/motor-boat-512.png"), "Status", this);
    mBoatPanel->setCheckable(true);
    ui->toolBar->addAction(mBoatPanel);

    mBoatSensors = new QAction(QIcon(":/icons/pictures/Boat icon/compass.png"), "Status", this);
    mBoatSensors->setCheckable(true);
    ui->toolBar->addAction(mBoatSensors);
}
