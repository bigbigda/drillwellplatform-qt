#include "enterdata.h"

void tableVLayout::addSearchItemSlot(){
    projectdompoint->tableinf[tabletype].tableRowNum ++;
    inTableWidget->setRowCount(projectdompoint->tableinf[tabletype].tableRowNum);

    inTableWidget->setVerticalHeaderItem(projectdompoint->tableinf[tabletype].tableRowNum-1,
        new QTableWidgetItem(QString::fromLocal8Bit("第")+QString::number(projectdompoint->tableinf[tabletype].tableRowNum-1)
        +QString::fromLocal8Bit("行")));

    QComboBox *tempCom;
    QString searchItem[5];
    for(int i=0;i<5;i++){
        tempCom = (QComboBox *)(this->inTableWidget->cellWidget(0,i));
        searchItem[i] = tempCom->currentText();
        inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(searchItem[i]));
    }

    for(int i=5;i<projectdompoint->tableinf[1].tableColNum;i++){
        inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(inTableWidget->item(0,i)->text()));
    }
}

void tableVLayout::searchSlot(){
    int ncount = 0;
    int nresult = -1;
    for (int i = 0; i < projectdompoint->cfilep[0]->actRowNum; i++){
        if((QComboBox *)(inTableWidget->cellWidget(0,0))->currentText() == "钻杆" && projectdompoint->cfilep[0]->fileData[0]=="A" ){
            for (int j0 = 1; j < 5; j++){
                if((QComboBox *)(inTableWidget->cellWidget(0,j0))->currentText() != projectdompoint->cfilep[0]->fileData[j0]){
                    break;
                }
                ncount ++;
                nresult = j0;
            }

        }else if(inTableWidget->cellWidget(0,0))->currentText() == "加重钻杆" && projectdompoint->cfilep[0]->fileData[0] == "B"{

    } else if(inTableWidget->cellWidget(0,0))->currentText() == "钻铤" && projectdompoint->cfilep[0]->fileData[0] == "C"){
        ;
    }
}

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
    inTableWidget->setItem(0,5,new QTableWidgetItem(""));
    inTableWidget->setItem(0,6,new QTableWidgetItem(""));
    inTableWidget->setItem(0,7,new QTableWidgetItem(""));
    inTableWidget->setItem(0,8,new QTableWidgetItem("1"));

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

    timeInfoLabel = new QLabel;
    if(projectdompoint->projectIsrealtime == false){
        timeInfoLabel->setText(QString::fromLocal8Bit("估算模式"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    //}else if(projectdompoint->showHasFinishFirst() == false){
    }else if(0){
        KaiCiNum kaici = projectdompoint->showKaiCiNum();
        timeInfoLabel->setText(QString::fromLocal8Bit("第")+ QString::number(kaici.kainum)+QString::fromLocal8Bit("开第")
                               +QString::number(kaici.cinum)+QString::fromLocal8Bit("次"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    } else{

        KaiCiNum kaici = projectdompoint->showKaiCiNum();
        timeInfoLabel->setText(QString::fromLocal8Bit("当前第")+ QString::number(kaici.kainum)+QString::fromLocal8Bit("开第")
                               +QString::number(kaici.cinum)+QString::fromLocal8Bit("次"));
        timeInfoLabel->setFont((QFont("Times", 18 , QFont::Bold) ));
        timeInfoLabel->setMaximumHeight(50);
    }

    QHBoxLayout  * selectKaiCiLayout = 0;
    QGroupBox    * radioGroupBox;
    QHBoxLayout  * radioGroupLayout;
//    QRadioButton * newKaiButton;
//    QRadioButton * newCiButton;
//    QPushButton  * confirmNewButton;

    //if(projectdompoint->projectIsrealtime && projectdompoint->showHasFinishFirst()){
    if(projectdompoint->projectIsrealtime){
        selectKaiCiLayout = new QHBoxLayout;

        newKaiButton = new QRadioButton(QString::fromLocal8Bit("新开"));
        newCiButton = new QRadioButton(QString::fromLocal8Bit("新次"));
        newCiButton->setChecked(true);
        radioGroupLayout = new QHBoxLayout;

        radioGroupLayout->addWidget(newKaiButton);
        radioGroupLayout->addWidget(newCiButton);

        radioGroupBox = new QGroupBox();
        radioGroupBox->setLayout(radioGroupLayout);

        confirmNewButton = new QPushButton(QString::fromLocal8Bit("确定"));
        confirmNewButton->setMaximumWidth(200);
        //confirmNewButton->setMinimumWidth(200);

        selectKaiCiLayout->addWidget(radioGroupBox);
        selectKaiCiLayout->addWidget(confirmNewButton,1);

        connect(confirmNewButton,SIGNAL(pressed()),this,SLOT(selKaiCi()));
    }

    QVBoxLayout * taoguanTable = 0;
    if(projectdompoint->projectIsrealtime){
        addLineData();
    }else{
        taoguanTable = new tableVLayout(tmpdompoint, 0);
    }

    QVBoxLayout * zuanjuzuheTable =   new tableVLayout(tmpdompoint, 1);

    QHBoxLayout * readzjDbLayout = new QHBoxLayout;
    QLabel * readzjDbLabel = new QLabel(QString::fromLocal8Bit("钻具详表:"));
    readzjDbLineEdit = new QLineEdit;
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
    submitButton->setMaximumHeight(65);
    submitButton->setMinimumHeight(55);

    layout = new QVBoxLayout();
    layout->addWidget(timeInfoLabel,Qt::AlignTop);
    layout->addItem(new QSpacerItem(1,8));
    if(projectdompoint->projectIsrealtime){
        if(1){
            layout->addLayout(selectKaiCiLayout);
            KaiD0Edit->setEnabled(0);
            KaiD1Edit->setEnabled(0);
            KaiD2Edit->setEnabled(0);
            KaiD3Edit->setEnabled(0);
            KaiD4Edit->setEnabled(0);
            KaiD5Edit->setEnabled(0);
            KaiD6Edit->setEnabled(0);
            CiD0Edit->setEnabled(0);
            CiD1Edit->setEnabled(0);
            CiD2Edit->setEnabled(0);
        }
        layout->addLayout(KaiLayout);
        layout->addLayout(CiLayout);
    }else{
        layout->addLayout(taoguanTable);
    }
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

void EnterData::selKaiCi()
{
    KaiCiNum kaici = projectdompoint->showKaiCiNum();
    if(newKaiButton->isChecked()){
        timeInfoLabel->setText(QString::fromLocal8Bit("第")+ QString::number(kaici.kainum + 1)+QString::fromLocal8Bit("开第")
                               +QString::number(1)+QString::fromLocal8Bit("次"));
    }else{
        timeInfoLabel->setText(QString::fromLocal8Bit("第")+ QString::number(kaici.kainum)+QString::fromLocal8Bit("开第")
                               +QString::number(kaici.cinum+1)+QString::fromLocal8Bit("次"));
    }
    newKaiButton->setEnabled(0);
    newCiButton->setEnabled(0);
    confirmNewButton->setEnabled(0);
    KaiD0Edit->setEnabled(1);
    KaiD1Edit->setEnabled(1);
    KaiD2Edit->setEnabled(1);
    KaiD3Edit->setEnabled(1);
    KaiD4Edit->setEnabled(1);
    KaiD5Edit->setEnabled(1);
    KaiD6Edit->setEnabled(1);
    CiD0Edit->setEnabled(1);
    CiD1Edit->setEnabled(1);
    CiD2Edit->setEnabled(1);
}

void EnterData::addLineData(){
    KaiLayout = new QGridLayout();
    QLabel *kaiLabel = new QLabel(QString::fromLocal8Bit("开信息"),this);
    kaiLabel->setFont((QFont("Times", 10 , QFont::Bold)));
    KaiLayout->addWidget(kaiLabel,0,0,1,2,Qt::AlignLeft);
    QLabel *kaiD0Label = new QLabel(QString::fromLocal8Bit("本开钻头直径（mm）："), this);
 //   kaiD0Label->setMaximumWidth(200);
 //   kaiD0Label->setMinimumWidth(200);
    KaiD0Edit = new QLineEdit;
    KaiD0Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD0Label, 1, 0);
    KaiLayout->addWidget(KaiD0Edit, 1, 1);

    QLabel *kaiD1Label = new QLabel(QString::fromLocal8Bit("井眼直径（m）:"), this);
//    kaiD1Label->setMaximumWidth(200);
//    kaiD1Label->setMinimumWidth(200);
    KaiD1Edit = new QLineEdit;
    KaiD1Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD1Label, 1, 2);
    KaiLayout->addWidget(KaiD1Edit, 1, 3);

    QLabel *kaiD2Label = new QLabel(QString::fromLocal8Bit("本开井段初始深度（m）:"), this);
//    kaiD2Label->setMaximumWidth(200);
//    kaiD2Label->setMinimumWidth(200);
    KaiD2Edit = new QLineEdit;
    KaiD2Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD2Label, 2, 0);
    KaiLayout->addWidget(KaiD2Edit, 2, 1);

    QLabel *kaiD3Label = new QLabel(QString::fromLocal8Bit("本开井段最终深度（m）:"), this);
//    kaiD3Label->setMaximumWidth(200);
//    kaiD3Label->setMinimumWidth(200);
    KaiD3Edit = new QLineEdit;
    KaiD3Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD3Label, 2, 2);
    KaiLayout->addWidget(KaiD3Edit, 2, 3);


    QLabel *kaiD4Label = new QLabel(QString::fromLocal8Bit("井段上端井深（m）:"), this);
//    kaiD4Label->setMaximumWidth(200);
//    kaiD4Label->setMinimumWidth(200);
    KaiD4Edit = new QLineEdit;
    KaiD4Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD4Label, 3, 0);
    KaiLayout->addWidget(KaiD4Edit, 3, 1);

    QLabel *kaiD5Label = new QLabel(QString::fromLocal8Bit("井段下端井深（m）:"), this);
//    kaiD5Label->setMaximumWidth(200);
//    kaiD5Label->setMinimumWidth(200);
    KaiD5Edit = new QLineEdit;
    KaiD5Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD5Label, 3, 2);
    KaiLayout->addWidget(KaiD5Edit, 3, 3);

    QLabel *kaiD6Label = new QLabel(QString::fromLocal8Bit("套管段摩擦系数 :"), this);
//    kaiD6Label->setMaximumWidth(200);
//    kaiD6Label->setMinimumWidth(200);
    KaiD6Edit = new QLineEdit;
    KaiD6Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    KaiLayout->addWidget(kaiD6Label, 4, 0);
    KaiLayout->addWidget(KaiD6Edit, 4, 1);

    CiLayout = new QGridLayout();
    QLabel *CiLabel = new QLabel(QString::fromLocal8Bit("次信息"),this);
    CiLabel->setFont((QFont("Times", 10 , QFont::Bold)));
    CiLayout->addWidget(CiLabel,0,0,1,2,Qt::AlignLeft);
    QLabel *CiD0Label = new QLabel(QString::fromLocal8Bit("本次钻具入井井深（m）:"), this);
//    CiD0Label->setMaximumWidth(200);
//    CiD0Label->setMinimumWidth(200);
    CiD0Edit = new QLineEdit;
    CiD0Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    CiLayout->addWidget(CiD0Label, 1, 0);
    CiLayout->addWidget(CiD0Edit, 1, 1);

    QLabel *CiD1Label = new QLabel(QString::fromLocal8Bit("本次钻具出井井深（m）:"), this);
//    CiD1Label->setMaximumWidth(200);
//    CiD1Label->setMinimumWidth(200);
    CiD1Edit = new QLineEdit;
    CiD1Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    CiLayout->addWidget(CiD1Label, 1, 2);
    CiLayout->addWidget(CiD1Edit, 1, 3);

    QLabel *CiD2Label = new QLabel(QString::fromLocal8Bit("裸眼段摩擦系数 :"), this);
//    CiD2Label->setMaximumWidth(200);
//    CiD2Label->setMinimumWidth(200);
    CiD2Edit = new QLineEdit;
    CiD2Edit->setValidator( new QDoubleValidator(0,100000,8,this));
    CiLayout->addWidget(CiD2Label, 2, 0);
    CiLayout->addWidget(CiD2Edit, 2, 1);
}
