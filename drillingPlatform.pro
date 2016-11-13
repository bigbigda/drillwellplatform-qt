#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T14:39:25
#
#-------------------------------------------------

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = drillingPlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    projectdom.cpp \
    createprowizard.cpp \
    calcwizard.cpp \
    waitingspinnerwidget.cpp \
    qcustomplot.cpp \
    plotview.cpp

HEADERS  += mainwindow.h \
    projectdom.h \
    createprowizard.h \
    calcwizard.h \
    waitingspinnerwidget.h \
    qcustomplot.h \
    plotview.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
