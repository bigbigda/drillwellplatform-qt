#ifndef READBASICEXCEL_H
#define READBASICEXCEL_H

#include <qdialog.h>
#include <projectdom.h>
#include <QBoxLayout>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QFileDialog>
#include <excelfile.h>

class ReadBasicExcel : public QDialog
{
public:
    ReadBasicExcel(ProjectDom * tmpdompoint ,QWidget *parent = 0);
    void browse1();
    void browse2();
    void browse3();
    void myupdate();
    bool readandcheckfile(QFileInfo fread1info,QFileInfo fread2info, QFileInfo fread3info);
    bool compareDepth();

    ProjectDom  *   projectdompoint;
    QLabel      *   jingyanLabel;
    QLineEdit   *   jingyanLineEdit;
    QPushButton *   browseButton1;
    QLabel      *   zuanjingyeLabel;
    QLineEdit   *   zuanjingyeLineEdit;
    QPushButton *   browseButton2;
    QLabel      *   zuanjinggongLabel;
    QLineEdit   *   zuanjinggongLineEdit;
    QPushButton *   browseButton3;
};

#endif // READBASICEXCEL_H
