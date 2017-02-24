#include "androidgps.h"

androidGps::androidGps(QObject *parent) : QObject(parent)
{
   QGeoPositionInfoSource *source1 = QGeoPositionInfoSource::createDefaultSource(0);

               connect(source1, SIGNAL(positionUpdated(QGeoPositionInfo)),
                       this, SLOT(positionUpdated(QGeoPositionInfo)));

               connect(source1, SIGNAL(error(QGeoPositionInfoSource::Error)),
                       this, SLOT(error(QGeoPositionInfoSource::Error)));

          if (source1) {
               source1->setUpdateInterval(1000);
               source1->startUpdates();


               qDebug() << "Gps1 status: " << source1->sourceName();
           }



           QGeoSatelliteInfoSource *source = QGeoSatelliteInfoSource::createDefaultSource(0);
           if (source)
           {
               source->setUpdateInterval(1000);
               source->startUpdates();
           }

           connect(source, SIGNAL(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)), this, SLOT(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)));

           qDebug() << source->sourceName() << "Source name";

}

void androidGps::positionUpdated(const QGeoPositionInfo &info)
{
    qDebug() << "GPS data source 1: " << info.isValid() << info;
}

void androidGps::error(QGeoPositionInfoSource::Error positioningError)
{
    qDebug() << "GPS ERROR Source1" << positioningError;
}

void androidGps::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &infos)
{
    qDebug() << "GPS data: ";
}
