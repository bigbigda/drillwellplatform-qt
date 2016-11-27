#include "enterdata.h"

void tableVLayout::addSearchItemSlot(){
    projectdompoint->tableinf[tabletype].tableRowNum ++;
    inTableWidget->setRowCount(projectdompoint->tableinf[tabletype].tableRowNum);

    inTableWidget->setVerticalHeaderItem(projectdompoint->tableinf[tabletype].tableRowNum-1,
        new QTableWidgetItem(QString::fromLocal8Bit("第")+QString::number(projectdompoint->tableinf[tabletype].tableRowNum-1)
        +QString::fromLocal8Bit("行")));

    QComboBox *tempCom;
    QString searchItem[5];
    if(((QComboBox *)(inTableWidget->cellWidget(0,0)))->currentText() == QString::fromLocal8Bit("钻杆")){
        for(int i=0;i<5;i++){
            tempCom = (QComboBox *)(this->inTableWidget->cellWidget(0,i));
            searchItem[i] = tempCom->currentText();
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(searchItem[i]));
        }

        for(int i=5;i<projectdompoint->tableinf[1].tableColNum;i++){
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(inTableWidget->item(0,i)->text()));
        }
    } else {
        for(int i=0;i<1;i++){
            tempCom = (QComboBox *)(this->inTableWidget->cellWidget(0,i));
            searchItem[i] = tempCom->currentText();
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(searchItem[i]));
        }
        for(int i=1;i<2;i++){
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(""));
            inTableWidget->item(projectdompoint->tableinf[1].tableRowNum-1,i)->setFlags(Qt::ItemIsEditable);
            inTableWidget->item(projectdompoint->tableinf[1].tableRowNum-1,i)->setBackgroundColor(QColor(Qt::lightGray));
        }
        for(int i=2;i<4;i++){
            tempCom = (QComboBox *)(this->inTableWidget->cellWidget(0,i));
            searchItem[i] = tempCom->currentText();
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(searchItem[i]));
        }
        for(int i=4;i<7;i++){
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(""));
            inTableWidget->item(projectdompoint->tableinf[1].tableRowNum-1,i)->setFlags(Qt::ItemIsEditable);
            inTableWidget->item(projectdompoint->tableinf[1].tableRowNum-1,i)->setBackgroundColor(QColor(Qt::lightGray));
        }
        for(int i=7;i<projectdompoint->tableinf[1].tableColNum;i++){
            inTableWidget->setItem(projectdompoint->tableinf[1].tableRowNum-1,i,new QTableWidgetItem(inTableWidget->item(0,i)->text()));
        }
    }

}

void tableVLayout::searchSlot(){
    int ncount = 0;
    int nresult = -1;
    for (int i = 0; i < projectdompoint->cfilep[0]->actRowNum; i++){
        if(((QComboBox *)(inTableWidget->cellWidget(0,0)))->currentText() == QString::fromLocal8Bit("钻杆") && projectdompoint->cfilep[0]->fileData[i].at(0)=="A" ){
            int compareColumCount = 0;
            for (int j0 = 1; j0 < 5; j0++){
                if(((QComboBox *)(inTableWidget->cellWidget(0,j0)))->currentText() != projectdompoint->cfilep[0]->fileData[i].at(j0)){
                    break;
                }
                compareColumCount++;
            }
            if(compareColumCount == 4){
               ncount ++;
               nresult = i;
            }
        } else if(((QComboBox *)(inTableWidget->cellWidget(0,0)))->currentText() == QString::fromLocal8Bit("加重钻杆") && projectdompoint->cfilep[0]->fileData[i].at(0) == "B"){
            int compareColumCount = 0;
            for (int j1 = 2; j1 < 4; j1++){
                if(((QComboBox *)(inTableWidget->cellWidget(0,j1)))->currentText() != projectdompoint->cfilep[0]->fileData[i].at(j1)){
                    break;
                }
                compareColumCount++;
            }
            if(compareColumCount == 2){
               ncount ++;
               nresult = i;
            }
        } else if(((QComboBox *)(inTableWidget->cellWidget(0,0)))->currentText() == QString::fromLocal8Bit("钻铤") && projectdompoint->cfilep[0]->fileData[i].at(0) == "C" ){
            int compareColumCount = 0;
            for (int j2 = 2; j2 < 4; j2++){
                if(((QComboBox *)(inTableWidget->cellWidget(0,j2)))->currentText() != projectdompoint->cfilep[0]->fileData[i].at(j2)){
                    qDebug()<<"===========================分割线";
                    qDebug()<<((QComboBox *)inTableWidget->cellWidget(0,j2))->currentText();
                    qDebug()<<projectdompoint->cfilep[0]->fileData[i].at(j2);
                    qDebug()<<"===========================分割线";
                    break;
                }
                compareColumCount ++;
            }
            if(compareColumCount == 2){
               ncount ++;
               nresult = i;
            }
        }
    }
    if(nresult == -1){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setText(QString::fromLocal8Bit("未找到此钻具"));
        msgBox.exec();
    }else{
        if(ncount > 1){
            QMessageBox msgBox;
            msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
            msgBox.setText(QString::fromLocal8Bit("找到多项"));
            msgBox.exec();
        }
        for (int k = 5; k < 8; k ++){
            inTableWidget->setItem(0, k, new QTableWidgetItem(projectdompoint->cfilep[0]->fileData[nresult].at(k)));
        }
            inTableWidget->setItem(0, 8, new QTableWidgetItem("1"));
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
    }else if(projectdompoint->showHasFinishFirst() == false){
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

    taoguanTable = 0;
    if(projectdompoint->projectIsrealtime){
        addLineData();
    }else{
        taoguanTable = new tableVLayout(tmpdompoint, 0);
    }

    zuanjuzuheTable =   new tableVLayout(tmpdompoint, 1);

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
    connect(submitButton, &QAbstractButton::clicked, this, &EnterData::submit);

    layout = new QVBoxLayout();
    layout->addWidget(timeInfoLabel,Qt::AlignTop);
    layout->addItem(new QSpacerItem(1,8));
    if(projectdompoint->projectIsrealtime){
        if(projectdompoint->showHasFinishFirst()){
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

void EnterData::submit(){

    if(readAndCheckTable() == false){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("套管表信息不符合规定"));
        msgBox.exec();
        projectdompoint->tableinf[0].fileData.clear();
        projectdompoint->tableinf[1].fileData.clear();
        return;
    }

    if(readExcel()==false){
        projectdompoint->tableinf[0].fileData.clear();
        projectdompoint->tableinf[1].fileData.clear();
        return;
    }

    qDebug()<<"@@@@@@"<<projectdompoint->efilep[3]->rowNum;
    qDebug()<<"@@@@@@"<<zuanjuzuheTable->inTableWidget->rowCount();

    int zuanjuNum = 0;
    for (int zuanjuTableRowCount = 1; zuanjuTableRowCount < zuanjuzuheTable->inTableWidget->rowCount(); zuanjuTableRowCount++){
        zuanjuNum +=  projectdompoint->tableinf[1].fileData[zuanjuTableRowCount-1].at(8).toInt();
    }
    qDebug()<<"&&&&"<<zuanjuNum;

    if((projectdompoint->efilep[3]->rowNum) != (zuanjuNum+ 1)){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("钻具详表与钻具性能数据行数不匹配"));
        msgBox.exec();
        projectdompoint->tableinf[0].fileData.clear();
        projectdompoint->tableinf[1].fileData.clear();
        return;
    }

    if(projectdompoint->projectIsrealtime){
        this->projectdompoint->tmpLineData.kaiLineD0 =  KaiD0Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD1 =  KaiD1Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD2 =  KaiD2Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD3 =  KaiD3Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD4 =  KaiD4Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD5 =  KaiD5Edit->text();
        this->projectdompoint->tmpLineData.kaiLineD6 =  KaiD6Edit->text();

        this->projectdompoint->tmpLineData.ciLineD0 =  CiD0Edit->text();
        this->projectdompoint->tmpLineData.ciLineD1 =  CiD1Edit->text();
        this->projectdompoint->tmpLineData.ciLineD2 =  CiD2Edit->text();
    }
    accept();
}

bool EnterData::readAndCheckTable(){

    //if(taoguanTable->inTableWidget->

//    qDebug()<<"rowNum:"<<taoguanTable->inTableWidget->rowCount();
//    qDebug()<<"colNum:"<<taoguanTable->inTableWidget->columnCount();

    if(projectdompoint->projectIsrealtime == false){
        for(int rowNum = 0; rowNum < taoguanTable->inTableWidget->rowCount(); rowNum ++){
            this->projectdompoint->tableinf[0].fileData.append(QStringList());
            for (int colNum = 0; colNum < taoguanTable->inTableWidget->columnCount(); colNum ++){
                if(taoguanTable->inTableWidget->item(rowNum,colNum)!=0){
                    this->projectdompoint->tableinf[0].fileData[this->projectdompoint->tableinf[0].fileData.count()-1]
                        .append(taoguanTable->inTableWidget->item(rowNum,colNum)->text());
                }else{
                    this->projectdompoint->tableinf[0].fileData[this->projectdompoint->tableinf[0].fileData.count()-1]
                        .append("");
                }
            }
        }

        int tmpkaiNumCount = 0;
        double tmpWellBottomDepth = 0;   //bottom in col 3
        for(int rowNum = 0; rowNum < this->projectdompoint->tableinf[0].fileData.count(); rowNum ++){
            qDebug() <<"^^"<< QString::number(tmpWellBottomDepth);
            if((tmpWellBottomDepth != 0 && this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt() < tmpkaiNumCount) ||
                this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt() == 0 ||
                this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble() < 0 ||
                (this->projectdompoint->tableinf[0].fileData[rowNum].at(3).toDouble() <=
                this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble()) ){
                qDebug()<<(this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt() == 0 );
                qDebug()<<(this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble() < 0 );
                qDebug()<<(this->projectdompoint->tableinf[0].fileData[rowNum].at(3).toDouble() <=
                           this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble()) ;
                qDebug()<<(this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt() < tmpWellBottomDepth);

                qDebug()<<"%%%";

                return false;
            }else{
                if(tmpkaiNumCount == 0){
                    tmpkaiNumCount = this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt();
                    tmpWellBottomDepth = this->projectdompoint->tableinf[0].fileData[rowNum].at(3).toDouble();
                } else if(tmpkaiNumCount == this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt()){
                    if(this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble() > tmpWellBottomDepth){
                        return false;
                    } else{
                        tmpWellBottomDepth = this->projectdompoint->tableinf[0].fileData[rowNum].at(3).toDouble();
                    }
                } else {
                    if ((tmpkaiNumCount+1) != this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt()){
                        return false;
                    } else if(this->projectdompoint->tableinf[0].fileData[rowNum].at(2).toDouble() != tmpWellBottomDepth){
                        return false;
                    } else{
                        tmpWellBottomDepth = this->projectdompoint->tableinf[0].fileData[rowNum].at(3).toDouble();
                        tmpkaiNumCount = this->projectdompoint->tableinf[0].fileData[rowNum].at(0).toInt();
                    }
                }
            }
         }
    }
    for(int rowNum = 1; rowNum < zuanjuzuheTable->inTableWidget->rowCount(); rowNum ++){
        this->projectdompoint->tableinf[1].fileData.append(QStringList());
        for (int colNum = 0; colNum < zuanjuzuheTable->inTableWidget->columnCount(); colNum ++){
            if(zuanjuzuheTable->inTableWidget->item(rowNum,colNum)!=0){
                this->projectdompoint->tableinf[1].fileData[this->projectdompoint->tableinf[1].fileData.count()-1]
                    .append(zuanjuzuheTable->inTableWidget->item(rowNum,colNum)->text());
            }else{
                this->projectdompoint->tableinf[1].fileData[this->projectdompoint->tableinf[1].fileData.count()-1]
                    .append("");
            }
        }
    }
    return true;
}

bool EnterData::readExcel(){
    QFileInfo fread4info(readzjDbLineEdit->text());

    if(!fread4info.exists() || !fread4info.isFile()){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("错误"));
        msgBox.setText(QString::fromLocal8Bit("钻具详表路径设置错误      "));
        msgBox.exec();
        return false;
    }
    projectdompoint->efilep[3] = new ExcelFile((fread4info.absoluteFilePath()),
                                              QString::fromLocal8Bit("钻具详表"),3,4,1,0);
    QAxObject*  excel = new QAxObject( "Excel.Application", 0 );
    QAxObject*  workbooks = excel->querySubObject("WorkBooks");
    if (!projectdompoint->efilep[3]->readExcel(workbooks))
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
    return true;

}


void EnterData::selKaiCi()
{
    KaiCiNum kaici = projectdompoint->showKaiCiNum();


    if(newKaiButton->isChecked()){
        projectdompoint->tmpKaiCiNum.kainum = kaici.kainum + 1;
        projectdompoint->tmpKaiCiNum.cinum = 1;
    }else{
        projectdompoint->tmpKaiCiNum.kainum = kaici.kainum;
        projectdompoint->tmpKaiCiNum.cinum = kaici.cinum + 1;
    }
    timeInfoLabel->setText(QString::fromLocal8Bit("第")+ QString::number(projectdompoint->tmpKaiCiNum.kainum)+QString::fromLocal8Bit("开第")
                           +QString::number(projectdompoint->tmpKaiCiNum.cinum)+QString::fromLocal8Bit("次"));
    newKaiButton->setEnabled(0);
    newCiButton->setEnabled(0);
    confirmNewButton->setEnabled(0);

    CiD0Edit->setEnabled(1);
    CiD1Edit->setEnabled(1);
    CiD2Edit->setEnabled(1);

    if(projectdompoint->tmpKaiCiNum.cinum == 1){
        KaiD0Edit->setEnabled(1);
        KaiD1Edit->setEnabled(1);
        KaiD2Edit->setEnabled(1);
        KaiD3Edit->setEnabled(1);
        KaiD4Edit->setEnabled(1);
        KaiD5Edit->setEnabled(1);
        KaiD6Edit->setEnabled(1);
    } else {
        //qDebug()<<
        KaiD0Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(0));
        KaiD1Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(1));
        KaiD2Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(2));
        KaiD3Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(3));
        KaiD4Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(4));
        KaiD5Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(5));
        KaiD6Edit->setText(this->projectdompoint->cfilep[2]->fileData.last().at(6));
    }

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
