#include "createprodialog.h"
#include "ui_createprodialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QDate>

CreateProDialog::CreateProDialog(const QString dir, ProjectDom *tmpdompoint, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProDialog)
{
    projectdompoint = tmpdompoint;
    ui->setupUi(this);
    ui->comboBox->addItem(dir);
    this->setFixedSize(525,281);
}

CreateProDialog::~CreateProDialog()
{
    delete ui;
}

QString CreateProDialog::BackProjectName()
{
    return ui->lineEdit->text();
}

QString CreateProDialog::BackProjectDir()
{
    return ui->comboBox->currentText();
}

void CreateProDialog::on_pushButton_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                            tr("Find Files"), QDir::currentPath());
    if (!directory.isEmpty()) {
        if (ui->comboBox->findText(directory) == -1)
            ui->comboBox->addItem(directory);
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));
    }

}



void CreateProDialog::on_pushButton_2_clicked()
{
    //判断该项目是否存在
    QDir dir;
    QString  folder = ui->comboBox->currentText()+"/"+ui->lineEdit->text();
    if(!dir.exists(folder))
    {
        //   projectdompoint->projectDir+"/"+projectdompoint->projectName+"/"+"text.dpro";
            dir.mkdir(folder);
    //char *m = folder.
        //qInfo(folder);
            projectdompoint->projectName = ui->lineEdit->text();
            projectdompoint->projectDir  = (ui->comboBox->currentText()+"/"+ui->lineEdit->text());
            CreateQDom();
            this->accept();
    } else
     {
        qInfo("exits folder");
        QMessageBox msgBox;
        msgBox.setText(QString::fromLocal8Bit("项目名冲突"));
        msgBox.exec();
    }

}

void CreateProDialog::CreateQDom()
{

    QDate date = QDate::currentDate();

    //写xml
    QDomProcessingInstruction instruction = projectdompoint->domDocument.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    projectdompoint->domDocument.appendChild(instruction);

    QDomElement Root = projectdompoint->domDocument.createElement("DP-Project");
    QDomElement BasicInfo = projectdompoint->domDocument.createElement("BasicInfo");
    QDomElement ProjectName = projectdompoint->domDocument.createElement("ProjectName");
    QDomElement ProjectDate = projectdompoint->domDocument.createElement("ProjectDate");

    QDomText nameText = projectdompoint->domDocument.createTextNode(projectdompoint->projectName);
    QDomText dateText = projectdompoint->domDocument.createTextNode(date.toString("yyyy-MM-dd"));
    ProjectName.appendChild(nameText);
    ProjectDate.appendChild(dateText);

    BasicInfo.appendChild(ProjectName);
    BasicInfo.appendChild(ProjectDate);
    Root.appendChild(BasicInfo);
    projectdompoint->domDocument.appendChild(Root);
}
