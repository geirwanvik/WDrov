#include "lapmessage.h"

LapMessage::LapMessage(QObject *parent) : QObject(parent)
{

}

QByteArray LapMessage::getTpStatus()
{
    quint16 dataSize = 3;
    quint8 messageID = 11;
    quint8 spec = 0;

    QByteArray sendTelemetry;

    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(spec);

    return sendTelemetry;
}

QByteArray LapMessage::getBatteryStatus()
{
    quint16 dataSize = 3;
    quint8 messageID = 14;
    quint8 spec = 0;

    QByteArray sendTelemetry;

    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(spec);

    return sendTelemetry;

}

QByteArray LapMessage::executeRelease()
{
    quint16 dataSize = 3;
    quint8 messageID = 16;
    quint8 spec = 0;

    QByteArray sendTelemetry;
    telemetryCounter++;
    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(spec);

    return sendTelemetry;
}

QByteArray LapMessage::getSensorsData()
{
    quint16 dataSize = 10;
    quint8 messageID = 15;
    quint8 spec = 0xFF;
    quint8 RFn = 0;

    QByteArray sendTelemetry;

    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(spec);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);
    sendTelemetry.append(RFn);

    return sendTelemetry;
}

QByteArray LapMessage::resetTp()
{
    quint16 dataSize = 3;
    quint8 messageID = 12;
    quint8 spec = 1;

    QByteArray sendTelemetry;

    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(spec);

    return sendTelemetry;
}

QByteArray LapMessage::getUtbData()
{
    quint16 dataSize = 2;
    quint8 messageID = 120;
    quint8 opPara = 1;
    QByteArray sendTelemetry;

    sendTelemetry.append(telemetryCounter++);
    sendTelemetry.append(dataSize);
    sendTelemetry.append(dataSize >> 8);
    sendTelemetry.append(messageID);
    sendTelemetry.append(opPara << 4);

    return sendTelemetry;

}
quint8 LapMessage::getTelemetryCounter() const
{
    return telemetryCounter;
}

void LapMessage::setTelemetryCounter(const quint8 &value)
{
    telemetryCounter = value;
}


