


win32{

    QT +=  serialport


}

android{

     QT += androidextras

}


unix:QT +=  serialport

unix || win32{
  SOURCES +=   Communication/Serial/serialport.cpp\
               Communication/Serial/serial_setup.cpp

  HEADERS += Communication/Serial/serialport.h\
             Communication/Serial/serial_setup.h

  FORMS += Communication/Serial/serial_setup.ui

}

