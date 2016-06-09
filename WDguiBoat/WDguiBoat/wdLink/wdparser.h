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

    void GpsData(QString command,QString value);
    void ImuData(QString command,QString value);
    void Dht22Data(QString command,QString value);
    void instrumentData(QString command,QString value);
    void PowerData(QString command,QString value);
    void LedFeedback(QString command,QString value);


public slots:
    void dataForParsing(QString string);

private slots:

private:
    void findCommand(QString command, QString value);
};

#endif // WDPARSER_H
