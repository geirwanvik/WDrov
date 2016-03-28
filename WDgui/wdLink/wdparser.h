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
    void noSupport(QStringList Stringlist);
    void fadePeriode(QString Periode);
    void fpsPeriode(QString periode);
    void LedMode(QString Mode);
    void LedBrightness(QString Brightness);
    void LedRGBvalues(QStringList RGBvalues);


public slots:
    void dataForParsing(QString string);

private slots:

private:
    QByteArray reSendData;
};

#endif // WDPARSER_H
