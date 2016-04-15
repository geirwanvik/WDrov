#ifndef SIO2UTBPROTOCOL_H
#define SIO2UTBPROTOCOL_H

#include <QObject>
#include <QThread>

#include "Communication/Bluetooth/bluetoothserial.h"
#include "crccnode.h"

class Sio2UtbProtocol : public QObject
{
    Q_OBJECT
public:
    explicit Sio2UtbProtocol(QObject *parent = 0);
    ~Sio2UtbProtocol();



signals:
    void writeBytes(QByteArray Array);

public slots:
    void writeSerialUtbData(QByteArray Data);
    void writeAcousticTestData(QByteArray Datafield);
    void requestUTBconfig(void);
    void requestUTBreset(void);
    void requestCnodeProductionInfo(void);
    void requestCnodeDiagnosticInfo(void);
    void downloadSoftware(QByteArray datafield, bool firstRun);

private:
    quint8 counter;
    void wakeUpSerial(void);
    void Sio2UtbWrite(qint16 length, QByteArray data, quint8 messageID, quint8 op, char typeCmd);
    void requestUtbData(qint8 messageID, qint8 op, char typeCmd);
    void requestCnodeData(qint8 messageID, qint8 op, char typeCmd);


};

#endif // SIO2UTBPROTOCOL_H
