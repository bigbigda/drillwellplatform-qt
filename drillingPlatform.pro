#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T14:39:25
#
#-------------------------------------------------

QT       += core gui xml
QT       += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

RC_ICONS = my2.ico

TARGET = drillingPlatform
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    projectdom.cpp \
    createprowizard.cpp \
    calcwizard.cpp \
    waitingspinnerwidget.cpp \
    qcustomplot.cpp \
    plotview.cpp \
    readbasicexcel.cpp \
    csvfile.cpp \
    enterdata.cpp \
    excelfile.cpp

HEADERS  += mainwindow.h \
    projectdom.h \
    createprowizard.h \
    calcwizard.h \
    waitingspinnerwidget.h \
    qcustomplot.h \
    plotview.h \
    readbasicexcel.h \
    csvfile.h \
    enterdata.h \
    excelfile.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon/image.qrc

DISTFILES +=
