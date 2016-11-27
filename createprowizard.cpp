#include "createprowizard.h"

CreateProWizard::CreateProWizard(ProjectDom *tmpdompoint, QWidget *parent)
  : QWizard(parent)
{
    projectdompoint = tmpdompoint;

    setPage(Page_Start, new CreateProPage);
    setPage(Page_Real, new KaiCiPage);
    setPage(Page_Esti, new EstimitPage);
    setPage(Page_End, new ProInfoPage);

    setWizardStyle(ClassicStyle);
    setWindowTitle(QString::fromLocal8Bit("计算"));
    setOption(QWizard::IndependentPages);
}

CreateProWizard::~CreateProWizard()
{

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
    QDomElement ProjectCategory = projectdompoint->domDocument.createElement("ProjectCategory");
    QDomElement ProjectStepSize = projectdompoint->domDocument.createElement("ProjectStepSize");

    QDomElement WellName  = projectdompoint->domDocument.createElement("WellName");
    QDomElement WellXing  = projectdompoint->domDocument.createElement("WellXing");
    QDomElement WellBie   = projectdompoint->domDocument.createElement("WellBie");
    QDomElement WellDepth = projectdompoint->domDocument.createElement("WellDepth");

    QDomElement DataBaseFile = projectdompoint->domDocument.createElement("DataBaseFile");

    QDomText nameText = projectdompoint->domDocument.createTextNode(projectdompoint->projectName);
    QDomText dateText = projectdompoint->domDocument.createTextNode(date.toString("yyyy-MM-dd"));
    QDomText categoryText;
    if(projectdompoint->projectIsrealtime){
        categoryText = projectdompoint->domDocument.createTextNode("RealTime");
    }else {
        categoryText = projectdompoint->domDocument.createTextNode("Forcast");
    }
    QDomText stepSize = projectdompoint->domDocument.createTextNode(field("FProjectStep").toString());
    QDomText wellname = projectdompoint->domDocument.createTextNode(field("FwellName").toString());
    QDomText wellxing = projectdompoint->domDocument.createTextNode(field("FwellXing").toString());
    QDomText wellbie = projectdompoint->domDocument.createTextNode(field("FwellFBie").toString());
    QDomText welldepth = projectdompoint->domDocument.createTextNode(field("FwellDepth").toString());
    QDomText databasefile = projectdompoint->domDocument.createTextNode(QCoreApplication::applicationDirPath()+"/default.csv");
    ProjectName.appendChild(nameText);
    ProjectDate.appendChild(dateText);
    ProjectCategory.appendChild(categoryText);
    ProjectStepSize.appendChild(stepSize);
    WellName.appendChild(wellname);
    WellXing.appendChild(wellxing);
    WellBie.appendChild(wellbie);
    WellDepth.appendChild(welldepth);
    DataBaseFile.appendChild(databasefile);

    BasicInfo.appendChild(ProjectName);
    BasicInfo.appendChild(ProjectDate);
    BasicInfo.appendChild(ProjectCategory);
    BasicInfo.appendChild(ProjectStepSize);
    BasicInfo.appendChild(WellName);
    BasicInfo.appendChild(WellXing);
    BasicInfo.appendChild(WellBie);
    BasicInfo.appendChild(WellDepth);
    BasicInfo.appendChild(DataBaseFile);

    Root.appendChild(BasicInfo);

    QDomElement SpecificInfo = projectdompoint->domDocument.createElement("SpecificInfo");

    if(projectdompoint->projectIsrealtime){
          QDomElement hasfinishfisrt = projectdompoint->domDocument.createElement("HasFinishFisrt");
          QDomElement StatusKai = projectdompoint->domDocument.createElement("CurrentkaiNo");
          QDomElement StatusCi = projectdompoint->domDocument.createElement("CurrentCiNo");
          QDomText hasfinishfisrtText = projectdompoint->domDocument.createTextNode("0");
          QDomText KaiText, CiText;
          if(field("fromNew").toBool()){
            KaiText = projectdompoint->domDocument.createTextNode("1");
            CiText = projectdompoint->domDocument.createTextNode("1");
          }else {
              KaiText = projectdompoint->domDocument.createTextNode(field("otherKaiNum").toString());
              CiText = projectdompoint->domDocument.createTextNode(field("otherCiNum").toString());
          }
          hasfinishfisrt.appendChild(hasfinishfisrtText);
          StatusKai.appendChild(KaiText);
          StatusCi.appendChild(CiText);
          SpecificInfo.appendChild(hasfinishfisrt);
          SpecificInfo.appendChild(StatusKai);
          SpecificInfo.appendChild(StatusCi);

    } else {
        QDomElement taoguanmcxs = projectdompoint->domDocument.createElement("taoguanmcxs");
        QDomElement luoyanmcxs = projectdompoint->domDocument.createElement("luoyanmcxs");
        QDomElement hasdetailzjzh = projectdompoint->domDocument.createElement("hasdetailzjzh");
        QDomText taoguanmcxsText = projectdompoint->domDocument.createTextNode(field("taoMoxi").toString());
        QDomText luoyanmcxsText = projectdompoint->domDocument.createTextNode(field("luoMoxi").toString());
        QDomText hasdetailzjzhText;
        if (field("hasXiangbzh").toBool()){
            hasdetailzjzhText = projectdompoint->domDocument.createTextNode("1");
        }else{
            hasdetailzjzhText = projectdompoint->domDocument.createTextNode("0");
        }
        taoguanmcxs.appendChild(taoguanmcxsText);
        luoyanmcxs.appendChild(luoyanmcxsText);
        hasdetailzjzh.appendChild(hasdetailzjzhText);
        SpecificInfo.appendChild(taoguanmcxs);
        SpecificInfo.appendChild(luoyanmcxs);
        SpecificInfo.appendChild(hasdetailzjzh);
    }
    Root.appendChild(SpecificInfo);

    projectdompoint->domDocument.appendChild(Root);
}

int CreateProPage::nextId() const
{
    if (realtimeProRadioButton->isChecked()) {
        return CreateProWizard::Page_Real;
    } else {
        return CreateProWizard::Page_Esti;
    }
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

    registerField("FproRealtime", realtimeProRadioButton);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;

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
  // qDebug() << groupBox->checkedId();
  // qDebug() << groupBox->checkedButton();

}

int KaiCiPage::nextId() const
{
    return CreateProWizard::Page_End;
}
KaiCiPage::KaiCiPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(QString::fromLocal8Bit("初始开次信息"));
   // setSubTitle(QString::fromLocal8Bit("确定第一次计算时开数和次数."));

    fromnewRadioButton = new QRadioButton(QString::fromLocal8Bit("& 从第1开第1次开始"));

    fromotherRadioButton = new QRadioButton(QString::fromLocal8Bit("& 指定开始开次"));

    KaiLabel = new QLabel(QString::fromLocal8Bit("&开始开数:"));
    KaiLineEdit = new QLineEdit;
    KaiLabel->setBuddy(KaiLineEdit);

    CiLabel = new QLabel(QString::fromLocal8Bit("&开始次数:"));
    CiLineEdit = new QLineEdit;
    CiLabel->setBuddy(CiLineEdit);

    KaiLineEdit->setValidator( new QIntValidator(0, 65536, this) );
    CiLineEdit->setValidator( new QIntValidator(0, 65536, this) );

    registerField("fromNew", fromnewRadioButton);
    registerField("otherKaiNum", KaiLineEdit);
    registerField("otherCiNum", CiLineEdit);

    connect(fromotherRadioButton, &QAbstractButton::toggled,
            KaiLineEdit, &QWidget::setEnabled);
    connect(fromotherRadioButton, &QAbstractButton::toggled,
            CiLineEdit, &QWidget::setEnabled);

    fromnewRadioButton->toggle();
    KaiLineEdit->setEnabled(0);
    CiLineEdit->setEnabled(0);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(fromnewRadioButton, 0, 0, 1, 3);
    layout->addWidget(fromotherRadioButton, 1, 0, 1, 3);
    layout->addWidget(KaiLabel, 2, 1);
    layout->addWidget(KaiLineEdit, 2, 2);
    layout->addWidget(CiLabel, 3, 1);
    layout->addWidget(CiLineEdit, 3, 2);

    setLayout(layout);

}

EstimitPage::EstimitPage(QWidget *parent)
{
    setTitle(QString::fromLocal8Bit("钻前估算模式设置"));

    TaoFLabel = new QLabel(QString::fromLocal8Bit("&套管段摩擦系数:"));
    TaoFLineEdit = new QLineEdit;
    TaoFLabel->setBuddy(TaoFLineEdit);

    LuoFLabel = new QLabel(QString::fromLocal8Bit("&裸眼段摩擦系数:"));
    LuoFLineEdit = new QLineEdit;
    LuoFLabel->setBuddy(LuoFLineEdit);

    TaoFLineEdit->setValidator( new QDoubleValidator(0, 10000, 3, this) );
    LuoFLineEdit->setValidator( new QDoubleValidator(0, 10000, 3, this) );

    groupBox = new QGroupBox(QString::fromLocal8Bit("详细钻具组合"));
    HasDetailRadioButton = new QRadioButton(QString::fromLocal8Bit("有"));
    DontHasDetailRadioButton = new QRadioButton(QString::fromLocal8Bit("无"));
    HasDetailRadioButton->setChecked(true);

    registerField("taoMoxi*", TaoFLineEdit);
    registerField("luoMoxi*", LuoFLineEdit);
    registerField("hasXiangbzh", HasDetailRadioButton);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->addWidget(HasDetailRadioButton);
    groupBoxLayout->addWidget(DontHasDetailRadioButton);
    groupBox->setLayout(groupBoxLayout);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(TaoFLabel, 1, 0);
    layout->addWidget(TaoFLineEdit, 1, 1);
    layout->addWidget(LuoFLabel, 2, 0);
    layout->addWidget(LuoFLineEdit, 2, 1);
    layout->addWidget(groupBox, 3, 0,1,3);

    setLayout(layout);
}

ProInfoPage::ProInfoPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(QString::fromLocal8Bit("基本信息"));
    setSubTitle(QString::fromLocal8Bit("在此处填写需要的基本信息，带*为必填项"));

   // setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

    wellNameLabel = new QLabel(QString::fromLocal8Bit("井名(*):"));
    wellNameLineEdit = new QLineEdit;
    wellNameLabel->setBuddy(wellNameLineEdit);

    projectStepSizeLabel = new QLabel(QString::fromLocal8Bit("计算步长(米)(≤9)(*):"));
    projectStepLineEdit = new QLineEdit;
    projectStepSizeLabel->setBuddy(wellNameLineEdit);

    projectStepLineEdit->setValidator( new QIntValidator(1, 9, this) );

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
    registerField("FProjectStep*", projectStepLineEdit);
    registerField("FwellXing", wellXingLineEdit);
    registerField("FwellFBie", wellBieLineEdit);
    registerField("FwellDepth", wellDepthLineEdit);
   // QSpacerItem* horizontalSpacer = new QSpacerItem(300, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(wellNameLabel, 0, 0);
    layout->addWidget(wellNameLineEdit, 0, 1);
    layout->addWidget(projectStepSizeLabel, 1, 0);
    layout->addWidget(projectStepLineEdit, 1, 1);
    //layout->addItem(horizontalSpacer,2,0,1,1);
    layout->addWidget(wellXingLabel, 3, 0);
    layout->addWidget(wellXingLineEdit, 3, 1);
    layout->addWidget(wellBieLabel, 4, 0);
    layout->addWidget(wellBieLineEdit, 4, 1);
    layout->addWidget(wellDepthLabel, 5, 0);
    layout->addWidget(wellDepthLineEdit, 5, 1);
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
    bool    projectisreal = field("FproRealtime").toBool();
    QString  folder = prodir+"/"+proname;
    QString Sstep = field("FProjectStep").toString();
    double Dstep = Sstep.toDouble();

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
            projectdompoint->projectIsrealtime = projectisreal;

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

