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

win32|macx {
INCLUDEPATH += "$$PWD/Win32/"

SOURCES += Win32/dummy_wiringPi.cpp\
        Win32/dummy_imu.cpp

HEADERS += Win32/wiringPi.h \
    Win32/wiringPiI2C.h \
    Win32/wiringPiSPI.h \
    Win32/wiringSerial.h \
    Win32/wiringShift.h
} else {
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/ -lwiringPi
INCLUDEPATH += $$PWD/../../../../usr/include
DEPENDPATH += $$PWD/../../../../usr/include
SOURCES += imu.cpp
}

SOURCES += main.cpp \
    server.cpp \
    imuhelperfunctions.cpp \
    mpu6050.cpp \
    WDlink.cpp \
    pca9685.cpp \
    motor.cpp

HEADERS += \
    server.h \
    imu.h \
    imuhelperfunctions.h \
    mpu6050.h \
    WDlink.h \
    pca9685.h \
    motor.h
