#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T11:59:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Video/configureipportdialog.cpp \
    Video/videoform.cpp \
    Client/clientsetupdialog.cpp \
    Client/tcpclient.cpp \
    Sensors/sensorsetupdialog.cpp \
    WD_Link/WDlink.cpp \
    RovWidgets/atttudeindicatorform.cpp \
    RovWidgets/compassform.cpp \
    RovWidgets/source/qcgaugewidget.cpp \
    Video/fontsizedialog.cpp \
    Video/overlaysettingsdialog.cpp


HEADERS  += mainwindow.h \
    Video/configureipportdialog.h \
    Video/videoform.h \
    Client/clientsetupdialog.h \
    Client/tcpclient.h \
    Sensors/sensorsetupdialog.h \
    WD_Link/WDlink.h \
    RovWidgets/atttudeindicatorform.h \
    RovWidgets/compassform.h \
    RovWidgets/source/qcgaugewidget.h \
    Video/fontsizedialog.h \
    Video/overlaysettingsdialog.h


FORMS    += mainwindow.ui \
    Video/configureipportdialog.ui \
    Video/videoform.ui \
    Client/clientsetupdialog.ui \
    Sensors/sensorsetupdialog.ui \
    RovWidgets/atttudeindicatorform.ui \
    RovWidgets/compassform.ui \
    Video/fontsizedialog.ui \
    Video/overlaysettingsdialog.ui




INCLUDEPATH +=C:\\OpenCV-3.1.0\\opencv\\build\\include

LIBS +=-LC:\\OpenCV-3.1.0\\mybuild\\lib\\Debug \
    -lopencv_core310d \
    -lopencv_features2d310d \
    -lopencv_flann310d \
    -lopencv_highgui310d \
    -lopencv_imgcodecs310d \
    -lopencv_imgproc310d \
    -lopencv_ml310d \
    -lopencv_objdetect310d \
    -lopencv_photo310d \
    -lopencv_shape310d \
    -lopencv_stitching310d \
    -lopencv_superres310d \
    -lopencv_ts310d \
    -lopencv_video310d \
    -lopencv_videoio310d \
    -lopencv_videostab310d \
    -lopencv_calib3d310d
