#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QCoreApplication>
#include <QFile>

#define MY_ASSERT(c) if (c == false) ;
#define MY_ASSERT_X(c, where, what) if (c == false) ;


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   // QFile file(QDate::currentDate().toString("Logg_dd_MM_yyyy.log"));
    QFile file("Logg");

    MY_ASSERT(file.open(QIODevice::Append | QIODevice::Text));

    QTextStream out(&file);

   /* switch (type)
    {
    case QtDebugMsg:    out << "DBG"; break;
   // case QtWarningMsg:  out << "WRN" ; break;
    case QtCriticalMsg: out << "CRT"; break;
    case QtFatalMsg:    out << "FTL"; break;
    }*/

    switch (type) {
    case 0:
        out << QTime::currentTime().toString("hh:mm:ss.zzz ");
        out << "DBG" " WD GUI Logg: " << msg << '\n'; break;
        break;
    case 4:
        out << QTime::currentTime().toString("hh:mm:ss.zzz ");
        out << "INFO" " WD GUI Logg: " << msg << '\n'; break;
        break;
    case 2:
        out << QTime::currentTime().toString("hh:mm:ss.zzz ");
        out << "CRT" " WD GUI Logg: " << msg << '\n'; break;
        break;
    case 3:
        out << QTime::currentTime().toString("hh:mm:ss.zzz ");
        out << "FTL" " WD GUI Logg: " << msg << '\n'; break;
        break;
    default:
        break;
    }
    out.flush();



}



int main(int argc, char *argv[])
{
    //Logging to file:
   // qInstallMessageHandler(myMessageOutput);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



