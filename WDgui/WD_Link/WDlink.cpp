#include "WDlink.h"
#include <QDebug>
WDlink::WDlink(QObject *parent) :
    QObject(parent)
{

}

void WDlink::NewMessage(QString &string)
{
    replyMessage = "";
    string = string.trimmed();
    string = string.remove('$');

    if (!CheckCRC(string))
    {
        return;
    }

    string = string.remove(string.lastIndexOf('*'),3);

    QStringList parsedList;
    parsedList = string.split(',');
    if (parsedList.isEmpty())
        return;

    emit GetTalker(parsedList.at(0));

    parsedList.removeFirst();

    if ((parsedList.length() % 2) != 0)
        return;


    for (int i = 0; i < parsedList.length(); i+=2)
    {
        emit GetMessageItem(parsedList.at(i),parsedList.at(i+1));
    }

    if (!replyMessage.isEmpty())
    {
        replyMessage = EncodeOutgoing(replyMessage);
        emit SendMessage(replyMessage);
    }
}

void WDlink::AddToReply(QString cmd, QString value)
{
    replyMessage += "," + cmd + "," + value;
}

void WDlink::sendWdLink(QString String)
{
    QString temp = EncodeOutgoing(String);
    emit WDlinkSend(temp);
  //  qDebug() << "WDlink send: " << temp;
    temp.clear();
}

QString WDlink::EncodeOutgoing(QString string)
{
    string.prepend("pi2");
    string.append("*");
    string += CalculateCRC(string);
    string.prepend("$");
    return string;
}

QString WDlink::CalculateCRC(const QString &string)
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

bool WDlink::CheckCRC(const QString &string)
{
    QString cCalculated, cReceived;
    cCalculated = CalculateCRC(string);
    int index = string.lastIndexOf('*');
    cReceived = string.mid(index +1);
    if (cReceived == cCalculated)
        return true;

    return false;
}
