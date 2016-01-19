#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T14:05:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

INCLUDEPATH += /usr/local/Cellar/opencv/2.4.12_2/include
LIBS += -L/usr/local/Cellar/opencv/2.4.12_2/lib/ -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

SOURCES += main.cpp\
        mainwindow.cpp \
        player.cpp gmm.cpp

HEADERS  += mainwindow.h \
            player.h \
            gmm.h

FORMS    += mainwindow.ui
