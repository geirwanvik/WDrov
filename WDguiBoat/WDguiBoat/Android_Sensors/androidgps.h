#ifndef ANDROIDGPS_H
#define ANDROIDGPS_H

#include <QObject>
#include <QDebug>
#include <QNmeaPositionInfoSource>
#include <QGeoSatelliteInfo>
#include <QGeoPositionInfo>
#include <QGeoSatelliteInfoSource>


class androidGps : public QObject
{
    Q_OBJECT
public:
    explicit androidGps(QObject *parent = 0);

signals:

public slots:

private slots:
    void positionUpdated(const QGeoPositionInfo &info);

    void error(QGeoPositionInfoSource::Error positioningError);


    void satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos);

private:
    QGeoSatelliteInfoSource *mGpsSource;
};

#endif // ANDROIDGPS_H
