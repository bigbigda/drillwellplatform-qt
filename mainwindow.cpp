#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    projectdompoint = 0;
    createprodialogPoint = 0;

    setWindowTitle(QString::fromLocal8Bit("钻井计算平台"));
//    setWindowIcon(QIcon(":/new/qt.png"));
    ui->action_set->setEnabled(false);
    ui->action_ReadExcel->setEnabled(false);
    ui->action_EnterData->setEnabled(false);
    ui->action_Cal->setEnabled(false);
    ui->action_Save->setEnabled(false);
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
                QString::fromLocal8Bit("Are you sure?\n"), QMessageBox::Cancel
                | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

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

    projectdompoint = new ProjectDom();
    createprodialogPoint = new CreateProWizard(this->projectdompoint,this);

    if(createprodialogPoint->exec() == QDialog::Accepted)
    {
        if(this->projectdompoint->projectIsrealtime){
            this->projectdompoint->tmpKaiCiNum = this->projectdompoint->showKaiCiNum();
            if(this->projectdompoint->tmpKaiCiNum.kainum == 0){
                this->projectdompoint->tmpKaiCiNum.kainum = 1;
                this->projectdompoint->setKaiCiNum(this->projectdompoint->tmpKaiCiNum);
                this->projectdompoint->setStartKaiCiNum(this->projectdompoint->tmpKaiCiNum);
            }
            if(this->projectdompoint->tmpKaiCiNum.cinum == 0){
                this->projectdompoint->tmpKaiCiNum.cinum = 1;
                this->projectdompoint->setKaiCiNum(this->projectdompoint->tmpKaiCiNum);
                this->projectdompoint->setStartKaiCiNum(this->projectdompoint->tmpKaiCiNum);
            }
        }

        this->projectdompoint->InitWriteXml();

        ui->action_ReadExcel->setEnabled(true);
        ui->action_set->setEnabled(true);
        ui->action_EnterData->setEnabled(false);
        ui->action_Cal->setEnabled(false);
    }
        delete createprodialogPoint;
}

void MainWindow::on_action_Open_triggered()
{
    if(projectdompoint != 0)
    {
        delete projectdompoint;
    }
    projectdompoint = new ProjectDom();

    QString file = QFileDialog::getOpenFileName(
                this,QString::fromLocal8Bit("打开项目"), "", "dp-project (*.dpro )"
                        );
    if (file != NULL)
    {
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
        if(this->projectdompoint->projectIsrealtime){
            this->projectdompoint->tmpKaiCiNum = this->projectdompoint->showKaiCiNum();
        }
        projectdompoint->projectIsrealtime = (ProjectCategory.text() == "RealTime");

        ui->action_ReadExcel->setEnabled(true);
        ui->action_set->setEnabled(true);
        ui->action_EnterData->setEnabled(false);
        ui->action_Cal->setEnabled(false);
    }
}


void MainWindow::on_action_Cal_triggered()
{
    CalcWizard * calcwizard = new CalcWizard(this->projectdompoint, this);
    calcwizard->exec();
}


void MainWindow::on_action_LaF_triggered()
{
    PlotView * plotpoint = new PlotView(this);
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

void MainWindow::on_action_ReadExcel_triggered()
{
    qDebug("!!!!!!!!!!!!!!!!!!!!");
    qDebug((QCoreApplication::applicationDirPath()).toLatin1());
    qDebug(QDir::currentPath().toLatin1());

    qDebug("!!!!!!!!!!!!!!!!!!!!");

    QString zuanjuDbPath = QCoreApplication::applicationDirPath()+"/zuanjuDb.csv";           //不变的数据库
    QFile Fout1(zuanjuDbPath);
    if(!Fout1.exists()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("钻具信息数据库不存在      "));
        msgBox.exec();
        return;
    }

    QFile Fout2(projectdompoint->showDataBaseFile());                      //全局的数据库
    if(!Fout2.exists()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("杆数据库(全局)不存在      "));
        msgBox.exec();
        return;
    }

    QString logData = QCoreApplication::applicationDirPath()+"/logData.csv";
    QFile Fout3(logData);
    qDebug()<<logData<<"&&&";
    if(projectdompoint->projectIsrealtime){
        if(!Fout3.exists()){
            QMessageBox msgBox;
            msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
            msgBox.setText(QString::fromLocal8Bit("开次配置记录文件不存在      "));
            msgBox.exec();
            qDebug()<<logData<<"&&&";
            return;
        }
        qDebug()<<logData<<"&&&";
        projectdompoint->cfilep[2] = new CsvFile(logData);
    }

    qDebug()<<projectdompoint->showDataBaseFile();
    qDebug()<<zuanjuDbPath;
    projectdompoint->cfilep[0] = new CsvFile(zuanjuDbPath);
    projectdompoint->cfilep[1] = new CsvFile(projectdompoint->showDataBaseFile());
    ReadBasicExcel * readbasicexcel = new ReadBasicExcel(this->projectdompoint, this);

    for (int i = 0; i < projectdompoint->cfilep[0]->fileData.count() ; i++)
    {
     projectdompoint->tableinf[1].tableConstData[2].append(projectdompoint->cfilep[0]->fileData[i].at(2));
     projectdompoint->tableinf[1].tableConstData[3].append(projectdompoint->cfilep[0]->fileData[i].at(3));
    }
    projectdompoint->tableinf[1].tableConstData[2].removeDuplicates();
    projectdompoint->tableinf[1].tableConstData[3].removeDuplicates();

    if (readbasicexcel->exec() == QDialog::Accepted)
    {
            ui->action_EnterData->setEnabled(true);
    }
        return;
}

void MainWindow::on_action_EnterData_triggered()
{
    EnterData*  enterdata = new EnterData(this->projectdompoint, this);
qDebug()<<"I am good1";
    //log data
    if(projectdompoint->projectIsrealtime){
//        this->projectdompoint->cfilep[2]->fileData.append(QStringList());
//        this->projectdompoint->cfilep[2]->fileData.last().append("2.1");
//        this->projectdompoint->cfilep[2]->fileData.last().append("0.8");
//        this->projectdompoint->cfilep[2]->fileData.last().append("47.4");
//        this->projectdompoint->cfilep[2]->fileData.last().append("58.3");
//        this->projectdompoint->cfilep[2]->fileData.last().append("45.3");
//        this->projectdompoint->cfilep[2]->fileData.last().append("60.3");
//        this->projectdompoint->cfilep[2]->fileData.last().append("0.56");
    }

qDebug()<<"I am good2";
    if (enterdata->exec() != QDialog::Accepted)
    {
      ui->action_Cal->setEnabled(true);
      ui->action_Save->setEnabled(true);
    }
    this->projectdompoint->tableinf[0].tableRowNum = 0;
    this->projectdompoint->tableinf[1].tableRowNum = 1;
    return;
}

void MainWindow::on_action_Save_triggered()
{
    if(this->projectdompoint->projectIsrealtime){
        this->projectdompoint->setKaiCiNum(this->projectdompoint->tmpKaiCiNum);
        if(!this->projectdompoint->showHasFinishFirst()){

            this->projectdompoint->setHasFinishFirst();

            this->projectdompoint->cfilep[2]->fileData.append(QStringList());
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD0);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD1);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD2);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD3);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD4);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD5);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD6);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD0);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD1);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD2);
        } else if(this->projectdompoint->showCiInfo() == 1){
            this->projectdompoint->cfilep[2]->fileData.append(QStringList());
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD0);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD1);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD2);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD3);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD4);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD5);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.kaiLineD6);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD0);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD1);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD2);
        } else{
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD0);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD1);
            this->projectdompoint->cfilep[2]->fileData.last().append(this->projectdompoint->tmpLineData.ciLineD2);
        }
    this->projectdompoint->tableinf[1].tableRowNum = 1;
    }

    ui->action_Cal->setEnabled(false);
    ui->action_Save->setEnabled(false);
}
