#include "calcwizard.h"
#include "waitingspinnerwidget.h"

CalcWizard::CalcWizard(ProjectDom *tmpprodompoint, QWidget *parent)
    : QWizard(parent)
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
 //   pronameLabel2->setText(QString::fromLocal8Bit("name_for_debug"));
    pronameLabel2->setText(projectdompoint->projectName);
    pronameLabel->setBuddy(pronameLabel2);
    procatLabel = new QLabel(QString::fromLocal8Bit("&项目类型 :"));
    procatLabel2 = new QLabel;
    if(projectdompoint->projectIsrealtime){
        procatLabel2->setText(QString::fromLocal8Bit("实时计算"));
    } else{
        procatLabel2->setText(QString::fromLocal8Bit("开钻前估算"));
    }
    procatLabel->setBuddy(procatLabel2);

    setstepLabel = new QLabel(QString::fromLocal8Bit("&步长（米）:"));
    setstepContentLabel = new QLabel;
    setstepContentLabel->setText(projectdompoint->showStepSize());
    setstepLabel->setBuddy(setstepContentLabel);

    layout1->addWidget(pronameLabel, 0, 0, 1, 1);
    layout1->addWidget(pronameLabel2, 0, 1, 1, 5);
    layout2->addWidget(procatLabel, 0, 0, 1, 1);
    layout2->addWidget(procatLabel2, 0, 1, 1, 5);
    layout3->addWidget(setstepLabel, 0, 0, 1, 1);
    layout3->addWidget(setstepContentLabel, 0, 1, 1, 5);
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
    torquecalcButton->setEnabled(1);
    connect(torquecalcButton, SIGNAL(clicked()),this, SLOT(on_torquecalcButton_clicked()));

    calcbutton = new QPushButton(QString::fromLocal8Bit("应力及疲劳损伤计算"));
  //  calcbutton->setEnabled(0);
    connect(calcbutton, SIGNAL(clicked()),this, SLOT(on_calcbutton_clicked()));
   // calcbutton->sizePolicy();

    QVBoxLayout *layout = new QVBoxLayout;
  //  layout->addWidget(fricforcButton,2);
    layout->addWidget(torquecalcButton,2);
    layout->addWidget(calcbutton,2);
    setLayout(layout);
}

void NiuFPage::on_fricforcButton_clicked()
{
    showandeditdialog = new ShowAndEditDialog(projectdompoint);
    showandeditdialog->exec();
    torquecalcButton->setEnabled(1);
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
    //    QLabel *lbl = new QLabel;
    //    QMovie *movie = new QMovie(":/images/logo1.png");
    //    lbl->setMovie(movie);
    //    lbl->show();
    //    movie->start();
        WaitingSpinnerWidget* spinner = new WaitingSpinnerWidget(parentwizardpoint, true, true);

        spinner->setRoundness(70.0);
        spinner->setMinimumTrailOpacity(15.0);
        spinner->setTrailFadePercentage(70.0);
        spinner->setNumberOfLines(12);
        spinner->setLineLength(10);
        spinner->setLineWidth(5);
        spinner->setInnerRadius(10);
        spinner->setRevolutionsPerSecond(1);
        spinner->setColor(QColor(81, 4, 71));

        spinner->start(); // gets the show on the road!
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("注意"));
        msgBox.setText(QString::fromLocal8Bit("计算完成"));
        msgBox.setInformativeText(QString::fromLocal8Bit("确定开始计算?"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        spinner->stop();
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
        WaitingSpinnerWidget* spinner = new WaitingSpinnerWidget(parentwizardpoint, true, true);

        spinner->setRoundness(70.0);
        spinner->setMinimumTrailOpacity(15.0);
        spinner->setTrailFadePercentage(70.0);
        spinner->setNumberOfLines(12);
        spinner->setLineLength(10);
        spinner->setLineWidth(5);
        spinner->setInnerRadius(10);
        spinner->setRevolutionsPerSecond(1);
        spinner->setColor(QColor(81, 4, 71));

        spinner->start(); // gets the show on the road!
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("注意"));
        msgBox.setText(QString::fromLocal8Bit("计算完成"));
        msgBox.setInformativeText(QString::fromLocal8Bit("确定开始计算?"));
      //  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      //  msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        spinner->stop();
        emit completeChanged();
//        QCustomPlot *customPlot;
//        customPlot->addGraph();
//        customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
//        customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
//        customPlot->addGraph();
//        customPlot->graph(1)->setPen(QPen(Qt::red));


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
    //注意摩擦系数的编辑精度和显示精度
     projectdompoint = tmpprodompoint;
    setWindowTitle(QString::fromLocal8Bit("显示/编辑摩擦系数"));
    // int frameStyle = QFrame::Sunken | QFrame::Panel;
     int frameStyle =  QFrame::Panel;

     taoguanLabel = new QLabel;
     taoguanLabel->setFrameStyle(frameStyle);
     QPushButton *integerButton =
             new QPushButton(QString::fromLocal8Bit("套管段摩擦系数"));
     taoguanLabel->setText(QString::number(123.123));

     luoyanLabel = new QLabel;
     luoyanLabel->setFrameStyle(frameStyle);
     QPushButton *doubleButton =
             new QPushButton(QString::fromLocal8Bit("裸眼段摩擦系数"));
     luoyanLabel->setText(QString::number(456.456));

     connect(integerButton, &QAbstractButton::clicked, this, &ShowAndEditDialog::setTaoguan);
     connect(doubleButton, &QAbstractButton::clicked, this, &ShowAndEditDialog::setLuoyan);

     QGridLayout *layout = new QGridLayout;

    // layout->setColumnStretch(10, 20);
     layout->setColumnMinimumWidth(1, 250);
     layout->addWidget(integerButton, 0, 0);
     layout->addWidget(taoguanLabel, 0, 1);

     layout->addWidget(doubleButton, 1, 0);
     layout->addWidget(luoyanLabel, 1, 1);
     layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);

     setLayout(layout);
}
void ShowAndEditDialog::setTaoguan()
{
//! [0]
    bool ok;
    double d1 = QInputDialog::getDouble(this,QString::fromLocal8Bit("修改"),
                                 QString::fromLocal8Bit("套管段摩擦系数:                    "),123.123, -214783647, 214783647, 5, &ok);
    if (ok)
        taoguanLabel->setText(QString::number(d1));
//! [0]
}
void ShowAndEditDialog::setLuoyan()
{
//! [1]
    bool ok;

    double d2 = QInputDialog::getDouble(this, QString::fromLocal8Bit("修改"),
                                       QString::fromLocal8Bit("裸眼段摩擦系数:                    "),456.456, -214783647, 214783647, 5, &ok);
    if (ok)
        luoyanLabel->setText(QString::number(d2));
//! [1]
}

