#include "sio2utbprotocol.h"

Sio2UtbProtocol::Sio2UtbProtocol(QObject *parent) : QObject(parent)
{

}

Sio2UtbProtocol::~Sio2UtbProtocol()
{

}

void Sio2UtbProtocol::requestUTBconfig()
{
    requestUtbData(120, 1, 'C');
}

void Sio2UtbProtocol::requestUTBreset()
{
    requestUtbData(120, 4, 'C');

}

void Sio2UtbProtocol::requestCnodeProductionInfo()
{
    requestUtbData(120, 5, 'C');
}

void Sio2UtbProtocol::requestCnodeDiagnosticInfo()
{
    requestUtbData(120, 6, 'C');
}

void Sio2UtbProtocol::downloadSoftware(QByteArray datafield, bool firstRun)
{
     QByteArray sendData;
     QByteArray tempData;

     tempData.append("APC2UTB");
     tempData.append(datafield);
     quint16 crc = CalculateCrc(tempData.constData()+7, tempData.length()-7);
     tempData.append(crc);
     tempData.append(crc >> 8);
     sendData.append(tempData);

     if(firstRun == true)
     {
         wakeUpSerial();
         thread()->msleep(50);
         wakeUpSerial();
         emit writeBytes(sendData);
     }
     else
     {
         emit writeBytes(sendData);
     }


}



void Sio2UtbProtocol::wakeUpSerial()
{
    QByteArray wakeUp;
    wakeUp = wakeUp.append((char) 0xAA);

    emit writeBytes(wakeUp);
}

void Sio2UtbProtocol::Sio2UtbWrite(qint16 length, QByteArray data, quint8 messageID, quint8 op, char typeCmd)
{
    QByteArray DataToSend;

    DataToSend.append("APC2UTB");
    DataToSend.append(length);
    DataToSend.append(length >> 8);
    DataToSend.append(counter++);
    DataToSend.append(0x01);
    DataToSend.append(typeCmd);
    DataToSend.append(messageID);
    DataToSend.append((op << 4));
    DataToSend.append(data);

    quint16 crc = CalculateCrc(DataToSend.constData() + 7, DataToSend.length()-7); //Preamble is not used in crc calculating

    DataToSend.append(crc);
    DataToSend.append(crc >> 8);

    emit writeBytes(DataToSend);


}

void Sio2UtbProtocol::requestUtbData(qint8 messageID, qint8 op, char typeCmd)
{
    QByteArray sendData;
    QByteArray preamble;

    preamble.append("APC2UTB"); //Preamble
    sendData.append(0x02); //Length
    sendData.append((char)0x00); //length
    sendData.append(counter++); // Sequence number 0-255
    sendData.append(0x01); //address
    sendData.append(typeCmd); // Type command C = configuration T = test
    sendData.append(messageID); // MessageID
    sendData.append((op << 4)); // Operating parameter
    quint16 crc = CalculateCrc(sendData.constData(), sendData.length());

    sendData.append(crc);
    sendData.append(crc >> 8);

    preamble.append(sendData);

    wakeUpSerial();
    thread()->msleep(50);
    wakeUpSerial();

    emit writeBytes(preamble);


}

void Sio2UtbProtocol::writeSerialUtbData(QByteArray Data)
{
    quint16 length = Data.length();
    QByteArray sendData;
    QByteArray preamble;

    preamble.append("APC2UTB"); //Preamble
    sendData.append(length); //Length
    sendData.append(length >> 8); //length
    sendData.append(counter++); // Sequence number 0-255
    sendData.append(0x01); //address
    sendData.append("C"); // Type command C = configuration T = test
    sendData.append(Data); //Add messageID and Op Parameter, then Datafield
    quint16 crc = CalculateCrc(sendData.constData(), sendData.length());

    sendData.append(crc);
    sendData.append(crc >> 8);

    preamble.append(sendData);

    wakeUpSerial();
    thread()->msleep(50);
    wakeUpSerial();

    emit writeBytes(preamble);

}

void Sio2UtbProtocol::writeAcousticTestData(QByteArray Datafield)
{
    quint16 length = Datafield.length();
    QByteArray sendData;
    QByteArray preamble;

    preamble.append("APC2UTB"); //Preamble
    sendData.append(length); //Length
    sendData.append(length >> 8); //length
    sendData.append(counter++); // Sequence number 0-255
    sendData.append(0x01); //address
    sendData.append("T"); // Type command C = configuration T = test
    sendData.append(Datafield); //Add messageID and Op Parameter, then Datafield
    quint16 crc = CalculateCrc(sendData.constData(), sendData.length());

    sendData.append(crc);
    sendData.append(crc >> 8);

    preamble.append(sendData);

    wakeUpSerial();
    thread()->msleep(50);
    wakeUpSerial();

    emit writeBytes(preamble);

}
