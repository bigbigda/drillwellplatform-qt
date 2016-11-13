#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <createprowizard.h>
#include <projectdom.h>
#include <QCloseEvent>
#include <calcwizard.h>
#include "qcustomplot.h"
#include "plotview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    projectdompoint = 0;
    createprodialogPoint = 0;
    setWindowTitle(QString::fromLocal8Bit("钻井计算平台"));

    ui->menu_3->setEnabled(0);
    ui->action_set->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    projectdompoint = 0;
    if(projectdompoint == 0)
    {
        event->accept();
    } else  if(projectdompoint->showNotSaveFlag()){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, projectdompoint->projectName,
                                                                QString::fromLocal8Bit("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
    }

}

void MainWindow::on_action_About_triggered()
{
      QMessageBox::aboutQt(this);
}

void MainWindow::on_action_Exit_triggered()
{
      this->close();
}


void MainWindow::on_action_New_triggered()
{
    if(projectdompoint != 0)
    {
        delete projectdompoint;
    }

    projectdompoint = new ProjectDom(QDomDocument());
    createprodialogPoint = new CreateProWizard(this->projectdompoint,this);

    if(createprodialogPoint->exec() == QDialog::Accepted)
    {
   //     qInfo() << "confirmed";

        this->projectdompoint->InitWriteXml();
    }
        delete createprodialogPoint;

    ui->menu_3->setEnabled(1);
    ui->action_set->setEnabled(1);
}

void MainWindow::on_action_Open_triggered()
{


    if(projectdompoint != 0)
    {
        delete projectdompoint;
    }

    projectdompoint = new ProjectDom(QDomDocument());

    QString file = QFileDialog::getOpenFileName(
                this,QString::fromLocal8Bit("打开项目"), "", "dp-project (*.dpro )"
                        );
    if (file != NULL)
    {
        QByteArray bytarr = file.toLatin1();
        qInfo(bytarr.data());
        //读取xml, 重建DOM
        QFile xmlFile(file);
        if (!xmlFile.exists() || !xmlFile.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
            msgBox.setText(QString::fromLocal8Bit("项目文件受损"));
            msgBox.exec();
         }
        projectdompoint->domDocument.setContent(&xmlFile);
        QDomElement DPProjectElement = projectdompoint->domDocument.firstChildElement();
        QDomElement BasicInfoElement = DPProjectElement.firstChildElement("BasicInfo");
        QDomElement ProjectNameElement = BasicInfoElement.firstChildElement("ProjectName");
        QDomElement ProjectCategory = BasicInfoElement.firstChildElement("ProjectCategory");

        projectdompoint->projectName = ProjectNameElement.text();
        projectdompoint->projectDir  = QFileInfo(xmlFile).absolutePath();

        projectdompoint->projectIsrealtime = (ProjectCategory.text() == "RealTime");

        ui->menu_3->setEnabled(1);
        ui->action_set->setEnabled(1);
    }
}


void MainWindow::on_action_Cal_triggered()
{
    CalcWizard * calcwizard = new CalcWizard(this->projectdompoint, this);
    calcwizard->exec();
}


void MainWindow::on_action_LaF_triggered()
{
    PlotView * plotpoint = new PlotView;
    plotpoint->exec();
}

void MainWindow::on_action_set_triggered()
{
  qDebug(projectdompoint->showDataBaseFile().toLatin1());
    QString file = QFileDialog::getOpenFileName(
                this,QString::fromLocal8Bit("设置全局数据库路径") , projectdompoint->showDataBaseFile(),"dp-project (*.csv )"
                        );
    if (file != NULL){
        projectdompoint->setDataBaseFile(file);
        qDebug(file.toLatin1());
    } else{
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("数据库设置错误      "));
        msgBox.exec();
    }

}
