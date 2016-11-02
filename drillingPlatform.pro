#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T14:39:25
#
#-------------------------------------------------

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drillingPlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createprodialog.cpp \
    projectdom.cpp

HEADERS  += mainwindow.h \
    createprodialog.h \
    projectdom.h

FORMS    += mainwindow.ui \
    createprodialog.ui
