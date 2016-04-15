#ifndef LAPMESSAGE_H
#define LAPMESSAGE_H

#include <QObject>
#include <QDebug>

class LapMessage : public QObject
{
    Q_OBJECT
public:
    explicit LapMessage(QObject *parent = 0);

    QByteArray getTpStatus();
    QByteArray getBatteryStatus();
    QByteArray executeRelease();
    QByteArray getSensorsData();
    QByteArray resetTp();
    QByteArray getUtbData();

    quint8 getTelemetryCounter() const;
    void setTelemetryCounter(const quint8 &value);

private:
    quint8 telemetryCounter;


signals:

public slots:
};

#endif // LAPMESSAGE_H
