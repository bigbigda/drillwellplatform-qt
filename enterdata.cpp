#include "enterdata.h"
#include <QStringList>
#include <QMessageBox>
#include <QLineEdit>
//class test : public QDialog
//{
//public:
//    test();
//};

//test::test()
//{
//    QLabel      *   mylabel = new QLabel;
//    mylabel->setText("aaaaaaaaaaaaa");
//    QVBoxLayout *inputLayout = new QVBoxLayout(this);
//    inputLayout->addWidget(mylabel);
//    QLabel      *   mylabel2 = new QLabel;
//    mylabel2->setText("bbbbbbbbbbb");
//    QVBoxLayout *inputLayout2 = new QVBoxLayout();
//    inputLayout2->addWidget(mylabel2);
//    delete(inputLayout);
//    setLayout(inputLayout2);
//}
#include "QPushButton"


void tableVLayout::removeRowSlot()
{
    if(tabletype == 0){
        if(projectdompoint->tableinf[tabletype].tableRowNum != 0){
            projectdompoint->tableinf[tabletype].tableRowNum --;
            inTableWidget->setRowCount(projectdompoint->tableinf[tabletype].tableRowNum);
        }
    }else if(tabletype == 1){
        if(projectdompoint->tableinf[tabletype].tableRowNum != 1){
            projectdompoint->tableinf[tabletype].tableRowNum --;
            inTableWidget->setRowCount(projectdompoint->tableinf[tabletype].tableRowNum);
        }
    }
}
void tableVLayout::addRowSlot()
{
    projectdompoint->tableinf[tabletype].tableRowNum ++;
    inTableWidget->setRowCount(projectdompoint->tableinf[tabletype].tableRowNum);
    if(tabletype == 0){
        inTableWidget->setVerticalHeaderItem(projectdompoint->tableinf[tabletype].tableRowNum-1,
            new QTableWidgetItem(QString::fromLocal8Bit("套管")+QString::number(projectdompoint->tableinf[tabletype].tableRowNum)
            +QString::fromLocal8Bit("段")));
    }
    else{
        inTableWidget->setVerticalHeaderItem(projectdompoint->tableinf[tabletype].tableRowNum-1,
            new QTableWidgetItem(QString::fromLocal8Bit("第")+QString::number(projectdompoint->tableinf[tabletype].tableRowNum-1)
            +QString::fromLocal8Bit("行")));
    }
}

tableVLayout::tableVLayout(ProjectDom *tmpdompoint, int type)
{
    tabletype = type;
    projectdompoint = tmpdompoint;

    QHBoxLayout *infoLayout = new QHBoxLayout();
    QLabel *tableLabel = new QLabel(projectdompoint->tableinf[tabletype].tableName);
    infoLayout->addWidget(tableLabel,Qt::AlignCenter);

    QFont font;
    font.setBold(true);
    tableLabel->setFont(font);

    if(tabletype == 1){
        QPushButton *selectButton = new QPushButton(QString::fromLocal8Bit("查询"));
        selectButton->setMinimumWidth(200);
        selectButton->setMaximumWidth(200);
        connect(selectButton,SIGNAL(pressed()),this,SLOT(searchSlot()));
        infoLayout->addWidget(selectButton);

        QPushButton *addItemButton = new QPushButton(QString::fromLocal8Bit("添加当前查询栏数据"));
        connect(addItemButton,SIGNAL(pressed()),this,SLOT(addRowSlot()));
        addItemButton->setMinimumWidth(200);
        addItemButton->setMaximumWidth(200);
        connect(addItemButton,SIGNAL(pressed()),this,SLOT(addSearchItemSlot()));
        infoLayout->addWidget(addItemButton);
    }

    QPushButton *addRowButton = new QPushButton(QString::fromLocal8Bit("新加行"));
    QPushButton *removeRowButton = new QPushButton(QString::fromLocal8Bit("删除行"));

    addRowButton->setMinimumWidth(200);
    addRowButton->setMaximumWidth(200);
    removeRowButton->setMinimumWidth(200);
    removeRowButton->setMaximumWidth(200);
    connect(addRowButton,SIGNAL(pressed()),this,SLOT(addRowSlot()));
    connect(removeRowButton,SIGNAL(pressed()),this,SLOT(removeRowSlot()));

    infoLayout->addWidget(addRowButton,Qt::AlignCenter);
    infoLayout->addWidget(removeRowButton,Qt::AlignCenter);

    tableLabel->setMaximumHeight(20);
    tableLabel->setMinimumHeight(15);

    inTableWidget = new QTableWidget(projectdompoint->tableinf[type].tableRowNum, projectdompoint->tableinf[type].tableColNum);
    inTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    inTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    inTableWidget->horizontalHeader()->setHidden(false);
    inTableWidget->verticalHeader()->setHidden(false);
    inTableWidget->setHorizontalHeaderLabels(projectdompoint->tableinf[type].tableRowHeadTag);

    if(tabletype == 1){
        inTableWidget->setVerticalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("查询栏")));
             QComboBox* combo = new QComboBox();
             inTableWidget->setCellWidget(0,3,combo);
        for(int i = 0; i < 5; i++){
            comboxArray[i] = new QComboBox();
            inTableWidget->setCellWidget(0,i,comboxArray[i]);
            comboxArray[i]->addItems(projectdompoint->tableinf[1].tableConstData[i]);
        }
    }

    this->addLayout(infoLayout);
    this->addWidget(inTableWidget);
}
EnterData::EnterData(ProjectDom *tmpdompoint, QWidget *parent): QDialog(parent)
{
    projectdompoint = tmpdompoint;
    setWindowTitle(QString::fromLocal8Bit("数据表"));
    resize(1000,700);

    QLabel  *  timeInfoLabel = new QLabel;
    if(0){
        timeInfoLabel->setText(QString::fromLocal8Bit("估算模式"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    }else if(0){
        timeInfoLabel->setText(QString::fromLocal8Bit("第1开第2次"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    } else if(1){
        timeInfoLabel->setText(QString::fromLocal8Bit("第1开第2次"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    }
    QGridLayout *KaiLayout = new QGridLayout();
    QLabel *kaiLabel = new QLabel(QString::fromLocal8Bit("开信息"),this);
    kaiLabel->setFont((QFont("Times", 10 , QFont::Bold)));
    KaiLayout->addWidget(kaiLabel,0,0,1,2,Qt::AlignCenter);
    QLabel *kaiD0Label = new QLabel(QString::fromLocal8Bit("本开钻头直径（mm）："), this);
    kaiD0Label->setMaximumWidth(200);
    kaiD0Label->setMinimumWidth(200);
    KaiLayout->addWidget(kaiD0Label, 1, 0);

    QLabel *kaiD1Label = new QLabel(QString::fromLocal8Bit("本开井段初始深度（m）："), this);
    kaiD1Label->setMaximumWidth(200);
    kaiD1Label->setMinimumWidth(200);
    KaiLayout->addWidget(kaiD1Label, 1, 1);

    QLabel *kaiD2Label = new QLabel(QString::fromLocal8Bit("本开井段最终深度（m）："), this);
    kaiD2Label->setMaximumWidth(200);
    kaiD2Label->setMinimumWidth(200);
    KaiLayout->addWidget(kaiD2Label, 2, 0);

    QLabel *kaiD3Label = new QLabel(QString::fromLocal8Bit("套管段摩擦系数 ："), this);
    kaiD3Label->setMaximumWidth(200);
    kaiD3Label->setMinimumWidth(200);
    KaiLayout->addWidget(kaiD3Label, 2, 1);

    QVBoxLayout * taoguanTable =   new tableVLayout(tmpdompoint, 0);
    QVBoxLayout * zuanjuzuheTable =   new tableVLayout(tmpdompoint, 1);

    QHBoxLayout * readzjDbLayout = new QHBoxLayout;
    QLabel * readzjDbLabel = new QLabel(QString::fromLocal8Bit("&钻具详表:"));
    readzjDbLineEdit = new QLineEdit;
    readzjDbLabel->setBuddy(readzjDbLineEdit);
  //  jingyanLineEdit->setText(projectdompoint->projectDir);
    QPushButton * browseButton1 = new QPushButton(tr("&Browse..."), this);
    QFont font;
    font.setBold(true);
    readzjDbLabel->setFont(font);
    readzjDbLineEdit->setMinimumHeight(35);
    browseButton1->setMinimumHeight(35);
    readzjDbLayout->addWidget(readzjDbLabel);
    readzjDbLayout->addWidget(readzjDbLineEdit);
    readzjDbLayout->addWidget(browseButton1);
    connect(browseButton1, &QAbstractButton::clicked, this, &EnterData::browse);

    QPushButton *submitButton = new QPushButton();
    submitButton->setText(QString::fromLocal8Bit("提交"));
    submitButton->setFont(QFont("Times", 12));
   // connect(submitButton,SIGNAL(pressed()),this,SLOT(submitSlot()));
    submitButton->setMaximumHeight(65);
      submitButton->setMinimumHeight(55);
    layout = new QVBoxLayout();
    layout->addWidget(timeInfoLabel,Qt::AlignTop);
    layout->addLayout(KaiLayout);
    layout->addLayout(taoguanTable);
    layout->addLayout(zuanjuzuheTable);
    layout->addLayout(readzjDbLayout);
    layout->addWidget(submitButton);


    setLayout(layout);
}

void EnterData::browse()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("钻井详表"),
                                                     projectdompoint->projectDir, "Excel files (*.xls *.xlsx)");
    readzjDbLineEdit->setText(filename);
}
