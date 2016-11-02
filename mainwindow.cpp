#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <createprodialog.h>
#include <projectdom.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageLabel(new QLabel)
{
    ui->setupUi(this);
    createprodialogPoint = new CreateProDialog(QDir::currentPath());
    projectdompoint = new ProjectDom(QDomDocument(),this);

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
    ui->actionA->setEnabled(true);
    //fitToWindowAct->setEnabled(true);
    //updateActions();

    //if (!fitToWindowAct->isChecked())
     //   imageLabel->adjustSize();
}

void MainWindow::on_action1_triggered()
{
  //QFileDialog dialog(this, tr("Open File!!!!!"));
  //initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
  //while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

    if(createprodialogPoint->exec() == QDialog::Accepted)
    {
        qInfo() << "confirmed";
        //qInfo() << createprodialogPoint->ui->linEdit->text();
        qInfo() << createprodialogPoint->BackProjectName();
        qInfo() << createprodialogPoint->BackProjectDir();
        QDomProcessingInstruction instruction = projectdompoint->domDocument.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
        projectdompoint->domDocument.appendChild(instruction);

        QDomElement root = projectdompoint->domDocument.createElement("DP-Project");
        projectdompoint->domDocument.appendChild(root);

        QDomElement basicInfo = projectdompoint->domDocument.createElement("BasicInfo");
        QDomText sNodeText = projectdompoint->domDocument.createTextNode("good");
        basicInfo.appendChild(sNodeText);
        root.appendChild(basicInfo);

        QFile file("text.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {}
        QTextStream out(&file);
        out.setCodec("UTF-8");
        projectdompoint->domDocument.save(out, 4, QDomNode::EncodingFromTextStream);
        file.close();


    }

}



void MainWindow::on_actionA_triggered()
{

}

void MainWindow::on_actionA_2_triggered()
{
    QMessageBox::aboutQt(this);
}
