#ifndef WDLINK_H
#define WDLINK_H

#include <QObject>
#include <inttypes.h>
#include <QStringList>
#include <QString>
#include <QTimer>

class WDlink: public QObject
{
    Q_OBJECT
public:
    WDlink(QObject *parent = 0);

public slots:
    void NewMessage(QString &string);
    void AddToReply(QString cmd, QString value);

signals:
    void GetMessageItem(QString cmd, QString value);
    void GetTalker(QString talker);
    void SendMessage(QString &string);

private:
    bool CheckCRC(const QString &string);
    QString CalculateCRC(const QString &string);
    QString EncodeOutgoing(QString string);
    QString replyMessage;

};

#endif // WDLINK_H
