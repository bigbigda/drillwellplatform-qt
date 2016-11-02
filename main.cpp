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
    QString path("C:\Users\nice\Desktop");
     QDir dir;
     dir.mkdir("C:\Users\nice\Desktop\123");

     //dir.mkpath("joh");
   /* if(QDir::mkpath("C:\Users\nice\Desktop\new_my"))
    {
        qInfo("mkdir sucsess");
    }else
    {
        qInfo("failed!");
    }
*/
      MainWindow w;
     w.show();

    return a.exec();
    QDomDocument doc;
        QDomDocument doc2;
    QFile file("my.xml");
/*    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))return 0;

    QXmlStreamWriter xml;
    xml.setDevice(&file);

    xml.writeStartDocument();
    xml.setAutoFormatting(true);
    xml.writeDTD("<!DOCTYPE DP-Project>");

    xml.writeStartElement("DP-Project");
    xml.writeStartElement("good");
    xml.writeAttribute("title","yes");
    xml.writeTextElement("this","Qt Project");

    xml.writeEndDocument();
    file.close();
    */
   if(!file.open(QIODevice::ReadOnly | QIODevice::Truncate))return 0;
      qInfo() << "++++++++++++++123";
   QXmlStreamReader xml_r;
    xml_r.setDevice(&file);
    while (!xml_r.atEnd() ){
           xml_r.readNextStartElement();
           if(xml_r.isStartElement()){
            qInfo() << xml_r.name();
            if(xml_r.name()== "mm"){
            qInfo() << xml_r.readElementText();
            }
        }

    }

    if(xml_r.hasError()) {

           qInfo() <<  xml_r.errorString();

            return 0;
    }
 /*
        QXmlStreamReader s;
    s.setDevice(&file);
    while (!s.atEnd()) {
               s.readNext();
               if (s.isStartElement() ) {
                   qInfo() << s.name();
                   qInfo() << s.readElementText();
               }
           }
*/

 //   return a.exec();
}
