#include "wdparser.h"


wdParser::wdParser(QObject *parent) : QObject(parent)
{

}

void wdParser::dataForParsing(QString string)
{
    string = string.trimmed();
    string = string.remove(string.lastIndexOf('*'),3);

    QStringList parsedList;
    parsedList = string.split(',');
    if (parsedList.isEmpty())
        return;

    parsedList.removeFirst(); // Remove talker

    if ((parsedList.length() % 2) != 0)
        return; // Must be even number of fields


    for (int i = 0; i < parsedList.length(); i += 2)
    {
        findCommand(parsedList.at(i), parsedList.at(i+1));
    }
}

void wdParser::findCommand(QString command, QString value)
{
    ushort i = 0;
    for (;i < sizeof(CommandString) / sizeof(CommandString[0]); i++)
    {
        if (command == CommandString[i])
        {
            break;
        }
    }
   // qDebug() << "Pac, implementer denne commandoen -> " << command << " " << value;
    switch (i)
    {
    case GPS_LAT:
    case GPS_LON:
    case GPS_GROUND_SPEED_KNOTS:
    case GPS_GROUND_SPEED_KMH:
    case GPS_GROUND_COURSE:
    case GPS_NUM_SATS:
    case GPS_HDOP:
    case GPS_X_SPEED:
    case GPS_Y_SPEED:
    emit GpsData(command, value);
        break;
    case IMU_ROLL:
    case IMU_PITCH:
    case IMU_HEADING:
    case IMU_RATE_OF_TURN:
    emit ImuData(command, value);
        break;
    case DHT22_TEMP:
    case DHT22_HUM:
    emit Dht22Data(command, value);
        break;
    case VOLTAGE:
    case CURRENT:
    emit PowerData(command, value);
        break;
    case LED_RED:
    case LED_GREEN:
    case LED_BLUE:
    case LED_STATUS:
    emit LedFeedback(command, value);
        break;
    case RELAY_BILGE_PP:
    case RELAY_INSTRUMENT:
    case RELAY_LANTERN:
    case RELAY_WIPER:
    case RELAY_SPARE5:
    case RELAY_SPARE6:
    case RELAY_SPARE7:
    case RELAY_SPARE8:
    case NODE_ALIVE:
    emit buttonPanelFeedback(command, value);
        break;
    default:
        qDebug() << "Ooops i fucked up" << command << value;
    }
}

