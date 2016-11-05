#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <createprowizard.h>
#include <projectdom.h>
#include <QCloseEvent>
#include <calcwizard.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageLabel(new QLabel)
{
    ui->setupUi(this);
    projectdompoint = 0;
    createprodialogPoint = 0;
    //  formPoint->show();
    //  ui->scrollArea->setBackgroundRole(QPalette::Base);
    //  ui->scrollArea->setWidget(imageLabel);
    //  ui->scrollArea->setVisible(true);
    //  ui->scrollArea->

}

MainWindow::~MainWindow()
{
    delete ui;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
/*    const QByteArrayList supportedMimeTypes = acceptMode != QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
        mimeTypeFilters.sort();
        dialog.setMimeTypeFilters(mimeTypeFilters);
        dialog.selectMimeTypeFilter("image/jpeg");
        if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("xxxx");
*/
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }
//! [2]

    setImage(newImage);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;
    imageLabel->setPixmap(QPixmap::fromImage(image));
//! [4]
    scaleFactor = 1.0;

    ui->scrollArea->setVisible(true);
    ui->action_Save->setEnabled(true);
    //fitToWindowAct->setEnabled(true);
    //updateActions();

    //if (!fitToWindowAct->isChecked())
     //   imageLabel->adjustSize();
}



void MainWindow::closeEvent (QCloseEvent *event)
{
    projectdompoint = 0;
    if(projectdompoint == 0)
    {
        event->accept();
    } else  if(projectdompoint->ProjectNotSaved()){
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


void MainWindow::on_action_Save_triggered()
{
    //保存
    this->projectdompoint->ProjectSaved();
}



void MainWindow::on_action_New_triggered()
{
    if(projectdompoint != 0)
    {
        delete projectdompoint;
    }

    projectdompoint = new ProjectDom(QDomDocument(),this);
    createprodialogPoint = new CreateProWizard(this->projectdompoint,this);

    if(createprodialogPoint->exec() == QDialog::Accepted)
    {
        qInfo() << "confirmed";

        this->projectdompoint->InitWriteXml();
    }
        delete createprodialogPoint;
}

void MainWindow::on_action_Open_triggered()
{


    if(projectdompoint != 0)
    {
        delete projectdompoint;
    }

    projectdompoint = new ProjectDom(QDomDocument(),this);

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
            msgBox.setText(QString::fromLocal8Bit("项目文件受损"));
            msgBox.exec();
         }
        projectdompoint->domDocument.setContent(&xmlFile);
        QDomElement DPProjectElement = projectdompoint->domDocument.firstChildElement();
        QDomElement BasicInfoElement = DPProjectElement.firstChildElement("BasicInfo");
        QDomElement ProjectNameElement = BasicInfoElement.firstChildElement("ProjectName");
        QString name = ProjectNameElement.text();
        projectdompoint->projectName = ProjectNameElement.text();
        projectdompoint->projectDir  = QFileInfo(xmlFile).absolutePath();

    }
}



void MainWindow::on_action_Cal_triggered()
{
    CalcWizard * calcwizard = new CalcWizard(this->projectdompoint);
    calcwizard->exec();
}


void MainWindow::on_pushButton2_clicked()
{

}
