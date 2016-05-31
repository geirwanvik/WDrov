#ifndef WDPARSER_H
#define WDPARSER_H

#include <QObject>
#include <QDebug>

#include <QTimer>

class wdParser : public QObject
{
    Q_OBJECT
public:
    explicit wdParser(QObject *parent = 0);

signals:
    void arduinoNode(QStringList StringList);
    void instrumentData(QStringList StringList);
    void ImuData(QStringList StringList);
    void Dht22Data(QStringList StringList);
    void GpsData(QStringList StringList);
    void PowerData(QStringList StringList);


public slots:
    void dataForParsing(QString string);

private slots:

private:
    QByteArray reSendData;
};

#endif // WDPARSER_H
