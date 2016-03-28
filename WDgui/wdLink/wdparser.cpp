#include "wdparser.h"

wdParser::wdParser(QObject *parent) : QObject(parent)
{

}

void wdParser::dataForParsing(QString string)
{
    QStringList fields = string.split(",");

    for(int i= 0; i < fields.length(); i++)
    {
      // qDebug() << fields[i];

    }


    if(fields.contains("KARMA"))
    {


      if(fields.contains("PERIODE") || fields.contains("FPS") || fields.contains("MODE") || fields.contains("BRIGHTNESS"))
      {
         emit fadePeriode(fields[2]);
         emit fpsPeriode(fields[4]);
         emit LedMode(fields[6]);
         emit LedBrightness(fields[8]);
         QStringList RGB;
         RGB << fields[9] << fields[10] << fields[11] << fields[12] << fields[13] << fields[14];
         emit LedRGBvalues(RGB);
         RGB.clear();

      }

    }
    else
    {
        emit noSupport(fields);
    }


}

