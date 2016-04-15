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


SOURCES += main.cpp\
        mainwindow.cpp \
    Palette/styleone.cpp \
    hmi/instrumentform.cpp \
    Communication/Bluetooth/bluetooth_setup.cpp \
    Communication/Bluetooth/bluetooththread.cpp

HEADERS  += mainwindow.h \
    Palette/styleone.h \
    hmi/instrumentform.h \
    Communication/Bluetooth/bluetooth_setup.h \
    Communication/Bluetooth/bluetooththread.h

FORMS    += mainwindow.ui \
    hmi/instrumentform.ui \
    Communication/Bluetooth/bluetooth_setup.ui

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

