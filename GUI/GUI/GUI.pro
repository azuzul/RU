#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T14:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_core -lopencv_imgproc -lopencv_highgui

SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    player.h

FORMS    += mainwindow.ui
