#include "createprowizard.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QDate>
#include <QtWidgets>

CreateProWizard::CreateProWizard(ProjectDom *tmpdompoint, QWidget *parent)

{
    projectdompoint = tmpdompoint;

    setWizardStyle(ClassicStyle);
    addPage(new CreateProPage);
    addPage(new ProInfoPage);
    setWindowTitle(QString::fromLocal8Bit("计算"));
    setOption(QWizard::IndependentPages);
}

CreateProWizard::~CreateProWizard()
{

}

QString CreateProWizard::BackProjectName()
{
    return 0;       //change
}

QString CreateProWizard::BackProjectDir()
{
    return 0;       //change
}

void CreateProWizard::CreateQDom()
{
    QDate date = QDate::currentDate();

    //写xml
    QDomProcessingInstruction instruction = projectdompoint->domDocument.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    projectdompoint->domDocument.appendChild(instruction);

    QDomElement Root = projectdompoint->domDocument.createElement("DP-Project");
    QDomElement BasicInfo = projectdompoint->domDocument.createElement("BasicInfo");
    QDomElement ProjectName = projectdompoint->domDocument.createElement("ProjectName");
    QDomElement ProjectDate = projectdompoint->domDocument.createElement("ProjectDate");
    QDomElement WellName  = projectdompoint->domDocument.createElement("WellName");
    QDomElement WellXing  = projectdompoint->domDocument.createElement("WellXing");
    QDomElement WellBie   = projectdompoint->domDocument.createElement("WellBie");
    QDomElement WellDepth = projectdompoint->domDocument.createElement("WellDepth");

    QDomText nameText = projectdompoint->domDocument.createTextNode(projectdompoint->projectName);
    QDomText dateText = projectdompoint->domDocument.createTextNode(date.toString("yyyy-MM-dd"));
    ProjectName.appendChild(nameText);
    ProjectDate.appendChild(dateText);

    BasicInfo.appendChild(ProjectName);
    BasicInfo.appendChild(ProjectDate);
    BasicInfo.appendChild(WellName);
    BasicInfo.appendChild(WellXing);
    BasicInfo.appendChild(WellBie);
    BasicInfo.appendChild(WellDepth);

    Root.appendChild(BasicInfo);
    projectdompoint->domDocument.appendChild(Root);
}

CreateProPage::CreateProPage(QWidget *parent)
    : QWizardPage(parent)
{

    setTitle(QString::fromLocal8Bit("创建项目"));
 //   setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

    QGridLayout *layout = new QGridLayout;
    proNameLabel = new QLabel(QString::fromLocal8Bit("&项目名:"));
    proNameLineEdit = new QLineEdit;
    proNameLabel->setBuddy(proNameLineEdit);

    proDirLabel = new QLabel(QString::fromLocal8Bit("&项目路径:"));
//    proDirLineEdit = new QLineEdit;
    proDirLineEdit = new QLineEdit;
    proDirLabel->setBuddy(proDirLineEdit);
    browseButton = new QPushButton(tr("&Browse..."), this);
    connect(browseButton, &QAbstractButton::clicked, this, &CreateProPage::browse);

    registerField("FproName*", proNameLineEdit);
    registerField("FproDir", proDirLineEdit);

    proDirLineEdit->setText(QDir::currentPath());

    groupBox = new QGroupBox(QString::fromLocal8Bit("项目类型"));
    realtimeProRadioButton = new QRadioButton(QString::fromLocal8Bit("实时监测/追算"));
    estimateProRadioButton = new QRadioButton(QString::fromLocal8Bit("开钻前估算"));

    realtimeProRadioButton->setChecked(true);
    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
//! [12]
    groupBoxLayout->addWidget(realtimeProRadioButton);
    groupBoxLayout->addWidget(estimateProRadioButton);
    groupBox->setLayout(groupBoxLayout);

    layout->addWidget(proNameLabel, 0, 0);
    layout->addWidget(proNameLineEdit, 0, 1,1,4);
    layout->addWidget(proDirLabel, 1, 0);
    layout->addWidget(proDirLineEdit, 1, 1,1,3);
    layout->addWidget(browseButton, 1, 4,1,1);
    layout->addWidget(groupBox, 3, 0,1,5);
   setLayout(layout);
}


ProInfoPage::ProInfoPage(QWidget *parent)
    : QWizardPage(parent)
{
//! [8]
    setTitle(QString::fromLocal8Bit("基本信息"));
    setSubTitle(QString::fromLocal8Bit("在此处填写需要的基本信息，带*为必填项"));

   // setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

//! [10]
    wellNameLabel = new QLabel(QString::fromLocal8Bit("井名:"));
    wellNameLineEdit = new QLineEdit;
    wellNameLabel->setBuddy(wellNameLineEdit);

    wellXingLabel = new QLabel(QString::fromLocal8Bit("井型:"));
    wellXingLineEdit = new QLineEdit;
    wellXingLabel->setBuddy(wellXingLineEdit);

    wellBieLabel = new QLabel(QString::fromLocal8Bit("井别:"));
    wellBieLineEdit = new QLineEdit;
    wellBieLabel->setBuddy(wellBieLineEdit);

    wellDepthLabel = new QLabel(QString::fromLocal8Bit("设计井深(米):"));
    wellDepthLineEdit = new QLineEdit;
    wellDepthLabel->setBuddy(wellDepthLineEdit);

    registerField("FwellName*", wellNameLineEdit);
    registerField("FwellXing", wellXingLineEdit);
    registerField("FwellFBie", wellBieLineEdit);
    registerField("FwellDepth", wellDepthLineEdit);


    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(wellNameLabel, 0, 0);
    layout->addWidget(wellNameLineEdit, 0, 1);
    layout->addWidget(wellXingLabel, 1, 0);
    layout->addWidget(wellXingLineEdit, 1, 1);
    layout->addWidget(wellBieLabel, 2, 0);
    layout->addWidget(wellBieLineEdit, 2, 1);
    layout->addWidget(wellDepthLabel, 3, 0);
    layout->addWidget(wellDepthLineEdit, 3, 1);
    setLayout(layout);

}

void CreateProPage::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());
    proDirLineEdit->setText(directory);

}

void CreateProWizard::accept()
{
    //判断该项目是否存在
    QString prodir  = field("FproDir").toString();
    QString proname = field("FproName").toString();
    QString  folder = prodir+"/"+proname;

    QDir dir;
    if(!dir.exists(folder))
    {
        if(dir.mkdir(folder) == false)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
            msgBox.setText(QString::fromLocal8Bit("创建项目失败,请检查创建路径"));
            msgBox.exec();
        } else
        {
            projectdompoint->projectName = proname;
            projectdompoint->projectDir  = prodir+"/"+proname;
            CreateQDom();
            QDialog::accept();
        }
    } else
     {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setText(QString::fromLocal8Bit("项目名冲突,请返回上级重新选择路径"));
        msgBox.exec();
    }

}

