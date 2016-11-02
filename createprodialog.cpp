#include "createprodialog.h"
#include "ui_createprodialog.h"
#include <QFileDialog>
#include <QMessageBox>
CreateProDialog::CreateProDialog(const QString dir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(dir);
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
            dir.mkdir(folder);
            this->accept();
    } else
     {
        qInfo("exits folder");
        QMessageBox msgBox;
        msgBox.setText(QString::fromLocal8Bit("项目名冲突"));
        msgBox.exec();
    }

}
