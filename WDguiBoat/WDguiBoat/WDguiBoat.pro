#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T21:34:50
#
#-------------------------------------------------

QT       += core gui
QT       += bluetooth
QT       += positioning
QT       += sensors


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDguiBoat
TEMPLATE = app

include(deployment.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    Palette/styleone.cpp \
    hmi/instrumentform.cpp \
    Communication/Bluetooth/bluetooth_setup.cpp \
    Communication/Bluetooth/bluetooththread.cpp \
    Screen/screendata.cpp \
    Scale/qscale.cpp \
    hmi/sensoroverviewform.cpp \
    progressBar/QProgressIndicator.cpp \
    hmi/ConfigClasses/sensorconfigdialog.cpp \
    wdLink/wdlink.cpp \
    wdLink/wdparser.cpp \
    hmi/allsensorsdialog.cpp \
    Android_Sensors/androidgps.cpp \
    Android_Sensors/androidaccelerometer.cpp \
    hmi/debug/wdlinkdebugdialog.cpp \
    hmi/seamapform.cpp \
    Android_Sensors/androidcompass.cpp \
    hmi/ConfigClasses/colordialog.cpp \
    mainwindowmenuactions.cpp \
    Android_Sensors/lightsensor.cpp \
    Android_Sensors/androidsensordialog.cpp


HEADERS  += mainwindow.h \
    Palette/styleone.h \
    hmi/instrumentform.h \
    Communication/Bluetooth/bluetooth_setup.h \
    Communication/Bluetooth/bluetooththread.h \
    Screen/screendata.h \
    Scale/qscale.h \
    hmi/sensoroverviewform.h \
    ../../WDboat/CommandList.h \
    progressBar/QProgressIndicator.h \
    hmi/ConfigClasses/sensorconfigdialog.h \
    wdLink/wdlink.h \
    wdLink/wdparser.h \
    hmi/allsensorsdialog.h \
    Android_Sensors/androidgps.h \
    Android_Sensors/androidaccelerometer.h \
    hmi/debug/wdlinkdebugdialog.h \
    hmi/seamapform.h \
    Android_Sensors/androidcompass.h \
    hmi/ConfigClasses/colordialog.h \
    Android_Sensors/lightsensor.h \
    Android_Sensors/androidsensordialog.h


FORMS    += mainwindow.ui \
    hmi/instrumentform.ui \
    Communication/Bluetooth/bluetooth_setup.ui \
    hmi/sensoroverviewform.ui \
    hmi/ConfigClasses/sensorconfigdialog.ui \
    hmi/allsensorsdialog.ui \
    hmi/debug/wdlinkdebugdialog.ui \
    hmi/seamapform.ui \
    hmi/ConfigClasses/colordialog.ui \
    Android_Sensors/androidsensordialog.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    pictureresources.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

