#ifndef ANDROIDCOMPASS_H
#define ANDROIDCOMPASS_H

#include <QObject>
#include <QCompass>
#include <QCompassReading>
#include <QCompassFilter>
#include <QDebug>

class androidCompass : public QObject
{
    Q_OBJECT
public:
    explicit androidCompass(QObject *parent = 0);
     QCompass *mCompass;

signals:

public slots:

private:

private slots:

};

#endif // ANDROIDCOMPASS_H
