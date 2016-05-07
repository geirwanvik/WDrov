#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T21:34:50
#
#-------------------------------------------------

QT       += core gui
QT       += bluetooth

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
    WD_Link/WDlink.cpp \
    progressBar/QProgressIndicator.cpp \
    hmi/ConfigClasses/sensorconfigdialog.cpp

HEADERS  += mainwindow.h \
    Palette/styleone.h \
    hmi/instrumentform.h \
    Communication/Bluetooth/bluetooth_setup.h \
    Communication/Bluetooth/bluetooththread.h \
    Screen/screendata.h \
    Scale/qscale.h \
    hmi/sensoroverviewform.h \
    CommandList.h \
    WD_Link/WDlink.h \
    progressBar/QProgressIndicator.h \
    hmi/ConfigClasses/sensorconfigdialog.h

FORMS    += mainwindow.ui \
    hmi/instrumentform.ui \
    Communication/Bluetooth/bluetooth_setup.ui \
    hmi/sensoroverviewform.ui \
    hmi/ConfigClasses/sensorconfigdialog.ui

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

