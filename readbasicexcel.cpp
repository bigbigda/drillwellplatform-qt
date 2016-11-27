#include "readbasicexcel.h"

ReadBasicExcel::ReadBasicExcel(ProjectDom * tmpdompoint ,QWidget *parent): QDialog(parent)
{
    projectdompoint = tmpdompoint;

    resize(400,200);
    setWindowTitle(QString::fromLocal8Bit("读取Excel表格"));

    jingyanLabel = new QLabel(QString::fromLocal8Bit("&井眼轨迹数据:"));
    jingyanLineEdit = new QLineEdit;
    jingyanLabel->setBuddy(jingyanLineEdit);
    jingyanLineEdit->setText(projectdompoint->projectDir);
    browseButton1 = new QPushButton(tr("&Browse..."), this);
    connect(browseButton1, &QAbstractButton::clicked, this, &ReadBasicExcel::browse1);

    zuanjingyeLabel = new QLabel(QString::fromLocal8Bit("&钻井液数据:"));
    zuanjingyeLineEdit = new QLineEdit;
    zuanjingyeLabel->setBuddy(zuanjingyeLineEdit);
    zuanjingyeLineEdit->setText(projectdompoint->projectDir);
    browseButton2 = new QPushButton(tr("&Browse..."), this);
    connect(browseButton2, &QAbstractButton::clicked, this, &ReadBasicExcel::browse2);

    zuanjinggongLabel = new QLabel(QString::fromLocal8Bit("&钻井工程参数:"));
    zuanjinggongLineEdit = new QLineEdit;
    zuanjinggongLabel->setBuddy(zuanjinggongLineEdit);
    zuanjinggongLineEdit->setText(projectdompoint->projectDir);
    browseButton3 = new QPushButton(tr("&Browse..."), this);
    connect(browseButton3, &QAbstractButton::clicked, this, &ReadBasicExcel::browse3);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(0, 20);
    layout->addWidget(jingyanLabel, 0, 0);
    layout->addWidget(jingyanLineEdit, 0, 1,1,3);
    layout->addWidget(browseButton1, 0, 4,1,1);
    layout->addWidget(zuanjingyeLabel, 1, 0);
    layout->addWidget(zuanjingyeLineEdit, 1, 1,1,3);
    layout->addWidget(browseButton2, 1, 4,1,1);
    layout->addWidget(zuanjinggongLabel, 2, 0);
    layout->addWidget(zuanjinggongLineEdit, 2, 1,1,3);
    layout->addWidget(browseButton3, 2, 4,1,1);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton(QString::fromLocal8Bit("更新"));
    okButton->setMaximumWidth(400);
    okButton->setMinimumWidth(300);
    buttonLayout->addWidget(okButton,Qt::AlignRight);
    QPushButton *cancelButton = new QPushButton(QString::fromLocal8Bit("取消"));
    cancelButton->setMaximumWidth(400);
    cancelButton->setMinimumWidth(300);
    buttonLayout->addWidget(cancelButton,Qt::AlignRight);
    layout->addLayout(buttonLayout,3,1,1,3);

    setLayout(layout);

    connect(okButton,&QAbstractButton::clicked,this,&ReadBasicExcel::myupdate);
    connect(cancelButton,SIGNAL(pressed()),this,SLOT(close()));
}

void ReadBasicExcel::browse1()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("井眼轨迹数据"),
                                                     projectdompoint->projectDir, "Excel files (*.xls *.xlsx)");
    jingyanLineEdit->setText(filename);
}

void ReadBasicExcel::browse2()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("钻井液数据"),
                                                     projectdompoint->projectDir, "Excel files (*.xls *.xlsx)");
    zuanjingyeLineEdit->setText(filename);
}

void ReadBasicExcel::browse3()
{
    QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("钻井工程参数"),
                                                     projectdompoint->projectDir, "Excel files (*.xls *.xlsx)");
    zuanjinggongLineEdit->setText(filename);
}

//QString file = QFileDialog::getOpenFileName(
//            this,QString::fromLocal8Bit("设置全局数据库路径") , projectdompoint->showDataBaseFile(),"dp-project (*.csv )"
//                    );

void ReadBasicExcel::myupdate()
{
    QFileInfo fread1info(jingyanLineEdit->text());
    QFileInfo fread2info(zuanjingyeLineEdit->text());
    QFileInfo fread3info(zuanjinggongLineEdit->text());
    if(!fread1info.exists() || !fread1info.isFile()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("井眼轨迹数据路径设置错误      "));
        msgBox.exec();
        return;
    }
    if(!fread2info.exists() || !fread2info.isFile()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("钻井液数据路径设置错误        "));
        msgBox.exec();
        return;
    }
    if(!fread3info.exists() || !fread3info.isFile()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("钻井工程参数路径设置错误      "));
        msgBox.exec();
        return;
    }

    if(readandcheckfile(fread1info, fread2info, fread3info))
    {
        accept();
    }
}

bool ReadBasicExcel::readandcheckfile(QFileInfo fread1info,QFileInfo fread2info, QFileInfo fread3info)
{
    QStringList wellTrackHHeader;
    QStringList drillFluitHHeader;
    QStringList drillProjectHHeader;
    int wellTrackCol;
    int drillFluitCol;
    int drillProjectCol;
    qDebug()<<fread1info.absoluteFilePath();
    wellTrackHHeader<<QString::fromLocal8Bit("测深L")<<QString::fromLocal8Bit("井斜角a")<<QString::fromLocal8Bit("方位角");
    wellTrackCol = 3;
    if(projectdompoint->projectIsrealtime){
        drillFluitHHeader<<"L D(i)"<<"L Mud(i-1)"<<"PV"<<"YP";
        drillProjectHHeader<<"L w(i)"<<"L w(i+1)"<<"PRM"<<"WOB"<<"TORQUE"<<"VOP"<<"ROP";

        drillFluitCol = 4;
        drillProjectCol = 7;
    } else {
        drillFluitHHeader<<"L D(i)"<<"PV"<<"YP";
        drillProjectHHeader<<"L D(i)"<<"WOB"<<"WOH"<<"RPM"<<"TORQUE"<<"ROP"<<"VOP"<<"MW out"<<"MW in";

        drillFluitCol = 3;
        drillProjectCol = 9;
    }
// .toUtf8()
    projectdompoint->efilep[0] = new ExcelFile((fread1info.absoluteFilePath()),
                                              QString::fromLocal8Bit("井眼轨迹数据"),0,3,1,0);
    projectdompoint->efilep[1] = new ExcelFile((fread2info.absoluteFilePath()),
                                              QString::fromLocal8Bit("钻井液数据"),0,4,1,0);
    projectdompoint->efilep[2] = new ExcelFile((fread3info.absoluteFilePath()),
                                              QString::fromLocal8Bit("钻井工程参数"),0,3,1,0);

    //read excel
    QAxObject*  excel = new QAxObject( "Excel.Application", 0 );
    QAxObject*  workbooks = excel->querySubObject("WorkBooks");
    if (!projectdompoint->efilep[0]->readExcel(workbooks) || !projectdompoint->efilep[1]->readExcel(workbooks)
            || !projectdompoint->efilep[2]->readExcel(workbooks))
    {
        excel->dynamicCall("Quit(void)");
        delete excel;
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("数据读取错误      "));
        msgBox.exec();
        return false;
    }
    excel->dynamicCall("Quit(void)");
    delete excel;
    if(!projectdompoint->efilep[0]->checkExcel() || !projectdompoint->efilep[1]->checkExcel() ||
            !projectdompoint->efilep[2]->checkExcel() || !compareDepth())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("请重新检查输入表格数据      "));
        msgBox.exec();
        return false;
    }
    return true;
}

bool ReadBasicExcel::compareDepth()
{
    QVariant lastLine1 = projectdompoint->efilep[1]->variantListData.last();
    QVariant lastLine2 = projectdompoint->efilep[2]->variantListData.last();

    if(lastLine1.toList().first().toDouble() != lastLine2.toList().first().toDouble())
    {
        return false;
    }
    return true;
}
