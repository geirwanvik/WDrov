#include "wdlink.h"

WDLink::WDLink(QObject *parent) : QObject(parent)
{
    state = Start;
}

void WDLink::Receive(QByteArray array)
{
    for(int i = 0; i < array.length(); i++)
    {
        char data = array.at(i);
        switch (state)
        {
        case Start:
            if (data == '$')
            {
                state = Receiving;
            }
            break;
        case Receiving:
            if ((data != '\r') && (data != '\n') && (data != 0))
            {
                rx += char(data);
                break;
            }
            else
            {
                state = End;
            }
        case End:
            if (CheckCRC(rx) == true)
            {
                emit freshData(rx);
            }
            rx.clear();
            state = Start;
            break;
        }
     }
}

void WDLink::Send(QString buffer)
{
    buffer.prepend("APP");
    buffer.append("*");
    buffer += CalculateCRC(buffer);
    buffer.prepend("$");
    buffer.append("\n");
    emit sendByteArrayToSocket(buffer.toLatin1());
    buffer.clear();
    qDebug() << "after wrappen: " << buffer;
}


QString WDLink::CalculateCRC(const QString &string)
{
    uint8_t i = 0, c = 0;
    while ((i < string.length()) && (string.at(i) != '*'))
    {
        c ^= (uint8_t)string.at(i).toLatin1();
        i++;
    }
    if (c < 0x10)
    {
        return ("0" + QString::number(c,16).toUpper());
    }
    return QString::number(c,16).toUpper();
}

bool WDLink::CheckCRC(const QString &string)
{
    QString cCalculated, cReceived;
    cCalculated = CalculateCRC(string);
    int index = string.lastIndexOf('*');
    cReceived = string.mid(index +1);
    if (QString::compare(cReceived,cCalculated,Qt::CaseInsensitive) == 0)
        return true;

    return false;
}
