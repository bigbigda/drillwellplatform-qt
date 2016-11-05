#include "calcwizard.h"

CalcWizard::CalcWizard(ProjectDom *tmpprodompoint)
{
    projectdompoint = tmpprodompoint;

    setWizardStyle(ModernStyle);
 //   setOption( QWizard::NoBackButtonOnLastPage, true );
    addPage(new SetStepPage(projectdompoint, this));
    addPage(new NiuFPage(projectdompoint, this));

    setWindowTitle(QString::fromLocal8Bit("计算"));
//    setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
//    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));
}

SetStepPage::SetStepPage(ProjectDom *tmpprodompoint, QWidget *parent)
    : QWizardPage(parent),
    projectdompoint(tmpprodompoint)
{
    setTitle(QString::fromLocal8Bit("设置步长"));
    setSubTitle(QString::fromLocal8Bit("本向导将引导您完成本工程对应拉力扭矩计算和疲劳损伤点计算"));

    QGridLayout *layout1 = new QGridLayout;
    QGridLayout *layout2 = new QGridLayout;
    QGridLayout *layout3 = new QGridLayout;

    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(label,0,0);

    pronameLabel = new QLabel(QString::fromLocal8Bit("&项目名称 :"));
    pronameLabel2 = new QLabel;
    pronameLabel2->setText(QString::fromLocal8Bit("name_for_debug"));
 //   pronameLabel2->setText(projectdompoint->projectName);
    pronameLabel->setBuddy(pronameLabel2);
    procatLabel = new QLabel(QString::fromLocal8Bit("&项目类型 :"));
    procatLabel2 = new QLabel;
    procatLabel2->setText(QString::fromLocal8Bit("开钻前估算"));
    procatLabel->setBuddy(procatLabel2);

    setstepLabel = new QLabel(QString::fromLocal8Bit("&步长（米）:"));
    setstepLineEdit = new QLineEdit;
    setstepLabel->setBuddy(setstepLineEdit);
    layout1->addWidget(pronameLabel, 0, 0, 1, 1);
    layout1->addWidget(pronameLabel2, 0, 1, 1, 5);
    layout2->addWidget(procatLabel, 0, 0, 1, 1);
    layout2->addWidget(procatLabel2, 0, 1, 1, 5);
    layout3->addWidget(setstepLabel, 0, 0);
    layout3->addWidget(setstepLineEdit, 0, 1);
    layout->addStretch(1);
    layout->addLayout(layout1);
    layout->addStretch(1);
    layout->addLayout(layout2);
    layout->addStretch(1);
    layout->addLayout(layout3);
    layout->addStretch(1);
    setLayout(layout);
}

NiuFPage::NiuFPage(ProjectDom * tmpprodompoint, QWizard *parent)
    : QWizardPage(parent),
     parentwizardpoint(parent),
     projectdompoint(tmpprodompoint)
{
    setTitle(QString::fromLocal8Bit("拉力扭矩计算及确认摩擦系数"));
    setSubTitle(QString::fromLocal8Bit("本页面提供对摩擦系数的修改以及拉力扭矩的计算，您"
                                       "可以根据拉力扭矩的计算结果修改摩擦系数并重新计算"));

 //   setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo1.png"));

    fricforcButton = new QPushButton(QString::fromLocal8Bit("显示/编辑摩擦系数"));
    connect(fricforcButton, SIGNAL(clicked()),this, SLOT(on_fricforcButton_clicked()));

    torquecalcButton = new QPushButton(QString::fromLocal8Bit("拉力扭矩计算:"));
    torquecalcButton->setEnabled(0);
    connect(torquecalcButton, SIGNAL(clicked()),this, SLOT(on_torquecalcButton_clicked()));

    calcbutton = new QPushButton(QString::fromLocal8Bit("计算"));
    calcbutton->setEnabled(0);
    connect(calcbutton, SIGNAL(clicked()),this, SLOT(on_calcbutton_clicked()));
   // calcbutton->sizePolicy();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(fricforcButton,2);
    layout->addWidget(torquecalcButton,2);
    layout->addWidget(calcbutton,2);
    setLayout(layout);
}

void NiuFPage::on_fricforcButton_clicked()
{
    showandeditdialog = new ShowAndEditDialog(projectdompoint);
    showandeditdialog->exec();
        torquecalcButton->setEnabled(0);
}
void NiuFPage::on_torquecalcButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("注意"));
    msgBox.setText(QString::fromLocal8Bit("开始进行全井段拉力扭矩计算，可能耗时较长，请您耐心等待"));
    msgBox.setInformativeText(QString::fromLocal8Bit("确定开始计算?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if (ret== QMessageBox::Ok){

        //进行计算，显示正在计算，计算完成后显示结果并提示是否需要修改摩擦系数并重新计算
        calcbutton->setEnabled(1);
    }else
    {

    }
}


void NiuFPage::on_calcbutton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("注意"));
    msgBox.setText(QString::fromLocal8Bit("开始进行应力计算计算和疲劳点计算，可能耗时较长，请您耐心等待"));
    msgBox.setInformativeText(QString::fromLocal8Bit("确定开始计算?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if (ret== QMessageBox::Ok){

        //进行计算，显示正在计算，计算完成后提示可以查看生成图像。
        emit completeChanged();
    }else
    {

    }
    emit completeChanged();
}

bool NiuFPage::isComplete()const
{
    if (calcbutton->isEnabled()) {
    return true;
    } else {
    return false;
    }
}

ShowAndEditDialog::ShowAndEditDialog(ProjectDom * tmpprodompoint, QWidget *parent)
{
     projectdompoint = tmpprodompoint;

}
