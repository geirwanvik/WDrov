#include "bluetooth_setup.h"
#include "ui_bluetooth_setup.h"

bluetooth_setup::bluetooth_setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bluetooth_setup)
{
    ui->setupUi(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this, SLOT(addDevice(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));
    connect(ui->listViewBluetoothDevices, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(stopScanning()));

    ui->pushButtonOk->setEnabled(false);
    this->setWindowState(Qt::WindowMaximized);

    ui->listViewBluetoothDevices->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QScroller::grabGesture(ui->listViewBluetoothDevices, QScroller::LeftMouseButtonGesture);

    createToolBar();

    hostStatus();

    ReadSettings();


}

bluetooth_setup::~bluetooth_setup()
{
    delete ui;
}



void bluetooth_setup::on_pushButtonScan_clicked()
{
    ui->pushButtonScan->setEnabled(false);
    ui->pushButtonOk->setEnabled(false);
    discoveryAgent->start();

}


void bluetooth_setup::on_pushButtonCancel_clicked()
{
   discoveryAgent->stop();
   ui->pushButtonOk->setEnabled(true);
   ui->pushButtonScan->setEnabled(true);
   this->hide();

}
void bluetooth_setup::on_pushButtonOk_clicked()
{
    updateAddress();
    emit PairDevicesNow();
    ui->listViewBluetoothDevices->clear();
    this->hide();
}

void bluetooth_setup::updateAddress()
{
    BluetoothAddress = bluetoothDevices[ui->listViewBluetoothDevices->currentItem()->text()];
    WriteSettings();
}
QString bluetooth_setup::getBluetoothAddress() const
{
    return BluetoothAddress;
}

void bluetooth_setup::setBluetoothAddress(const QString &value)
{
    BluetoothAddress = value;
}


void bluetooth_setup::WriteSettings()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("Bluetooth");
    settings.setValue("BluetoothAdress",BluetoothAddress);
    settings.endGroup();
}

void bluetooth_setup::ReadSettings()
{
    QSettings settings("WD Electronics", "WDBoat");
    settings.beginGroup("Bluetooth");
    BluetoothAddress = settings.value("BluetoothAdress").toString();
    settings.endGroup();

}

void bluetooth_setup::createToolBar()
{
    LabelToolBar = new QLabel(this);
    LabelToolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    LabelToolBar->setAlignment(Qt::AlignCenter);
    LabelToolBar->setText("Bluetooth Setup");

    ToolBar = new QToolBar(this);
    ToolBar->addWidget(LabelToolBar);

    this->layout()->setMenuBar(ToolBar);
}



void bluetooth_setup::addDevice(const QBluetoothDeviceInfo &info)
{
    bluetoothDevices.insert(info.name() ,info.address().toString());


   // QString label = QString("%2 %1").arg(info.address().toString()).arg(info.name()); //Hvis vi bare ønsker navnet på modulen
    QString label = QString("%1").arg(info.name());
    QList<QListWidgetItem *> items = ui->listViewBluetoothDevices->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
         ui->listViewBluetoothDevices->addItem(item);

}




}

void bluetooth_setup::scanFinished()
{
    ui->pushButtonScan->setEnabled(true);
}


void bluetooth_setup::stopScanning()
{
    discoveryAgent->stop();
    ui->pushButtonOk->setEnabled(true);
    ui->pushButtonScan->setEnabled(true);
    BluetoothAddress = bluetoothDevices[ui->listViewBluetoothDevices->currentItem()->text()];

}


QString bluetooth_setup::getAddress()
{
    return BluetoothAddress;
}


int bluetooth_setup::hostStatus()
{
    return localdevice.hostMode();
}

void bluetooth_setup::turnBluetoothOn()
{
    localdevice.powerOn();
}
