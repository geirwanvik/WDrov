#include "wdparser.h"

wdParser::wdParser(QObject *parent) : QObject(parent)
{

}

void wdParser::dataForParsing(QString string)
{
    QStringList fields = string.split(",");

   /* for(int i= 0; i < fields.length(); i++)
    {
       qDebug() << fields[i];

    }*/


    if(fields.contains("ardu"))
    {
        fields.removeFirst();

      if(fields.contains("RELAY_BILGE_PP") || fields.contains("RELAY_LANTERN") || fields.contains("RELAY_WIPER"))
      {
            emit instrumentData(fields);
      }
      else if(fields.contains("DHT22_TEMP") || fields.contains("DHT22_HUM"))
      {
          emit Dht22Data(fields);
      }
      else if(fields.contains("GPS_LAT") || fields.contains("GPS_LON") || fields.contains("GPS_ALT"))
      {
          emit GpsData(fields);
         // qDebug () << fields[6] << fields[7] << "  " << fields[8] << fields[9] << fields[10] << fields[11] << fields[12] << fields[13];
      }
      else if(fields.contains("IMU_ROLL") || fields.contains("IMU_PITCH") || fields.contains("IMU_HEADING"))
      {
          emit ImuData(fields);
        //  qDebug () << fields[0] << fields[1] << "  " << fields[2] << fields[3] << "  " << fields[4] << fields[5];
      }
      else if(fields.contains("VOLTAGE") || fields.contains("CURRENT"))
      {
          emit PowerData(fields);
      }
      else
      {
          return;
      }

    }
    else
    {

    }


}

