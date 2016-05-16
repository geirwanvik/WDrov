#include "wdlink.h"

WDLink::WDLink(QObject *parent) : QObject(parent)
{
    state = Start;


    connect(this, SIGNAL(freshSendData(QString)), this, SLOT(sendFreshSocketData(QString)));
}

void WDLink::Receive(unsigned char data)
{


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
            if (CheckCRC(rx.toStdString().c_str()))
            {
                unsigned char index = rx.lastIndexOf('*');
                rx.remove(index,3);
                emit freshData(rx);
            }
            rx = "";
            state = Start;
            break;
        }



}

void WDLink::Send(QString *buffer) //Adding protocoll data to a string
{
    char crcHex[2];
        tx += '$';
        tx += *buffer;
        unsigned char crc = CalculateCRC(buffer->toStdString().c_str());
        tx += '*';
        sprintf(crcHex,"%02x", crc);
        tx += crcHex;


        emit freshSendData(tx);

        tx.clear();
}



unsigned char WDLink::CalculateCRC(const char *buffer)
{
    unsigned char c = 0;
        while (*buffer)
        {
            c ^= *buffer++;
        }
        return c;
}

unsigned char WDLink::CheckCRC(const char *buffer)
{
    unsigned char c = 0;
        unsigned char crc = 0;
        while (*buffer != '*')
        {
            c ^= *buffer++;
        }
        buffer++;
        crc = strtoul(buffer, 0, 16);

        if (c == crc)
        {
            return true;
        }
        return false;
}



void WDLink::ReveiveSlot(unsigned char data) //Wd link decoder
{
    switch (state)
    {
    case Start:
        if (data == '$')
        {
            state = Receiving;
        }
        break;
    case Receiving:
        if ((data != '\r') && (data != '\n') && (data != '0'))
        {
            rx += char(data);
            break;
        }
        else
        {
            state = End;
        }
    case End:
        if (CheckCRC(rx.toStdString().c_str()))
        {
            unsigned char index = rx.lastIndexOf('*');
            rx.remove(index,3);
           emit freshData(rx);
        }
        rx = "";
        state = Start;
        break;
    }
}

void WDLink::inncommingData(QByteArray Array) //Data from inncomming socket in bytearray
{
  //  qDebug() << Array;
    for(int i = 0; i < Array.length(); i++)
    {
        Receive(Array.at(i));
    }
}

void WDLink::sendFreshSocketData(QString string) //Send to socket/serialport Array
{
    string += '\n';
    QByteArray array(string.toStdString().c_str(), string.length());

    emit sendByteArrayToSocket(array);

    array.clear();
}

void WDLink::sendData(QString buffer) //Wd link data packer adding $ and crc
{
    char crcHex[2];
        tx += '$';
        tx += buffer;
        unsigned char crc = CalculateCRC(buffer.toStdString().c_str());
        tx += '*';
        sprintf(crcHex,"%02x", crc);
        tx += crcHex;

        qDebug() << "After wrapping: " << tx;
        emit freshSendData(tx);

        tx.clear();



}


