#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <QDomDocument>
#include <QtXml>
#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtWidgets>
#include <stdio.h>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     MainWindow w;
     w.show();

    return a.exec();

}
