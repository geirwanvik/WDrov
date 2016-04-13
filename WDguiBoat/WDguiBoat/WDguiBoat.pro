#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T21:34:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDguiBoat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Palette/styleone.cpp

HEADERS  += mainwindow.h \
    Palette/styleone.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    pictureresources.qrc

