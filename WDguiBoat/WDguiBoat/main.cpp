#include "mainwindow.h"
#include <QApplication>




#ifdef Q_OS_ANDROID

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{


    Q_UNUSED(context)

    QFile outFile(qgetenv("EXTERNAL_STORAGE") + QStringLiteral("/WD-Boat/WDBoat-log.txt"));

    // EXTERNAL_STORAGE determines writable inner storage of device, for memory card use SECONDARY_STORAGE, but it may not exists
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Append)) { // append line by line
            QTextStream out(&outFile);

            switch (type) {
            case 0:
                out << QTime::currentTime().toString("hh:mm:ss.zzz ");
                out << "DBG" " WD Logg: " << msg << '\n'; break;
                break;
            case 4:
                out << QTime::currentTime().toString("hh:mm:ss.zzz ");
                out << "INFO" " WD Logg: " << msg << '\n'; break;
                break;
            case 2:
                out << QTime::currentTime().toString("hh:mm:ss.zzz ");
                out << "CRT" " WD Logg: " << msg << '\n'; break;
                break;
            case 3:
                out << QTime::currentTime().toString("hh:mm:ss.zzz ");
                out << "FTL" " WD Logg: " << msg << '\n'; break;
                break;
            default:
                break;
            }
            out.flush();
      }

#else

#define MY_ASSERT(c) if(c == false){};
#define MY_ASSERT_X(c, where, what) if (c == false) ;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
      Q_UNUSED(context); //Not used

      QFile file("WD_Logg");

      MY_ASSERT(file.open(QIODevice::Append | QIODevice::Text));

      QTextStream out(&file);

      switch (type) {
      case 0:
          out << QTime::currentTime().toString("hh:mm:ss.zzz ");
          out << "DBG" " WD Logg: " << msg << '\n'; break;
          break;
      case 4:
          out << QTime::currentTime().toString("hh:mm:ss.zzz ");
          out << "INFO" " WD Logg: " << msg << '\n'; break;
          break;
      case 2:
          out << QTime::currentTime().toString("hh:mm:ss.zzz ");
          out << "CRT" " WD Logg: " << msg << '\n'; break;
          break;
      case 3:
          out << QTime::currentTime().toString("hh:mm:ss.zzz ");
          out << "FTL" " WD Logg: " << msg << '\n'; break;
          break;
      default:
          break;
      }
      out.flush();
}
#endif

#ifdef Q_OS_ANDROID
}
#endif

int main(int argc, char *argv[])
{

#if defined (Q_OS_ANDROID)
     QString logFile(qgetenv("EXTERNAL_STORAGE") + QStringLiteral("/WD-Boat/WDBoat-log.txt"));
     QString logFolder(qgetenv("EXTERNAL_STORAGE") + QStringLiteral("/WD-Boat"));
     if(QDir(logFolder).exists())
     {
        QFileInfo fileinfo(logFile);
        if (QFile::exists(logFile) && (fileinfo.size() > 2000000)) // remove previous file if exists
        {
            QFile::remove(logFile);
        }

     }
     else
     {
         QDir().mkdir(logFolder);

     }


   //qInstallMessageHandler(myMessageOutput);
   qDebug() << "==== WD Boat LOG =======\n" << QDateTime::currentDateTime().toString(); // first log message
 #endif


#ifdef Q_OS_WIN
  // qInstallMessageHandler(myMessageOutput);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
