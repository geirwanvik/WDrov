#-------------------------------------------------
#
# Project created by QtCreator 2016-02-23T18:46:46
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = WDcore
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    imu.cpp \
    imuhelperfunctions.cpp \
    mpu6050.cpp \
    WDlink.cpp \
    pca9685.cpp \
    motor.cpp

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include

HEADERS += \
    server.h \
    imu.h \
    imuhelperfunctions.h \
    mpu6050.h \
    WDlink.h \
    pca9685.h \
    motor.h
