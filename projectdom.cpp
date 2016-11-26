#include "projectdom.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

ProjectDom::ProjectDom(QDomDocument document)
    :domDocument (document)
{
    projectSaved();
    InitTableStruct();
}

void ProjectDom::InitTableStruct()
{
    tableinf[0].tableName = QString::fromLocal8Bit("套管信息");
    tableinf[0].tableColNum = 5;
    tableinf[0].tableRowNum = 0;
    tableinf[0].tableRowHeadTag.append(QString::fromLocal8Bit("开数"));
    tableinf[0].tableRowHeadTag.append(QString::fromLocal8Bit("井眼直径"));
    tableinf[0].tableRowHeadTag.append(QString::fromLocal8Bit("井段上端井深"));
    tableinf[0].tableRowHeadTag.append(QString::fromLocal8Bit("井段下端井深"));
    tableinf[0].tableRowHeadTag.append(QString::fromLocal8Bit("钻头直径"));


    tableinf[1].tableName = QString::fromLocal8Bit("钻具组合与性能数据");
    tableinf[1].tableColNum = 9;
    tableinf[1].tableRowNum = 1;
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("钻具名称"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("钢级"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("内径"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("外径"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("接头型号"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("接头外直径"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("接头长度"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("线重"));
    tableinf[1].tableRowHeadTag.append(QString::fromLocal8Bit("钻具数量"));

    tableinf[1].tableConstData[0] << QString::fromLocal8Bit("钻杆") << QString::fromLocal8Bit("加重钻杆") << QString::fromLocal8Bit("钻铤");
    tableinf[1].tableConstData[1] << "G" << "S";
    tableinf[1].tableConstData[2] << "60.325";
    tableinf[1].tableConstData[3] << "73.025";
    tableinf[1].tableConstData[4] << "NC26" << "NC31" <<"NC40" <<"NC46" << "NC50" << "5 1/2FH" << "6 5/8FH";
}
void ProjectDom::projectChanged()
{
    this->flagNeedToSave = true;
}

void ProjectDom::projectSaved()
{
    this->flagNeedToSave = false;
}

bool    ProjectDom::showNotSaveFlag()
{
    return  flagNeedToSave;
}

void    ProjectDom::InitWriteXml()
{
    QFile file(this->projectDir+"/"+this->projectName+".dpro");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("警告"));
        msgBox.setText(QString::fromLocal8Bit("写文件错误,请检查"));
        msgBox.exec();
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    this->domDocument.save(out, 4, QDomNode::EncodingFromTextStream);
    file.close();
}

int ProjectDom::showKaiInfo()
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("StatusInfo");
    QDomElement KaiNoElement = StatusInfoElement.firstChildElement("KaiNo");
    int kai = KaiNoElement.text().toDouble();
    return kai;
}

int ProjectDom::showCiInfo()
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("StatusInfo");
    QDomElement CiNoElement = StatusInfoElement.firstChildElement("CiNo");
    int ci = CiNoElement.text().toDouble();
    return ci;
}

double  ProjectDom::backStepSize()
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("BasicInfo");
    QDomElement CiNoElement = StatusInfoElement.firstChildElement("ProjectStepSize");
    int ci = CiNoElement.text().toDouble();
    return ci;
}

QString  ProjectDom::showStepSize()
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("BasicInfo");
    QDomElement CiNoElement = StatusInfoElement.firstChildElement("ProjectStepSize");
    return CiNoElement.text();
}

QString ProjectDom::showDataBaseFile()
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("BasicInfo");
    QDomElement DataBaseElement = StatusInfoElement.firstChildElement("DataBaseFile");
    return DataBaseElement.text();

}
void    ProjectDom::setDataBaseFile(QString newfile)
{
    QDomElement DPProjectElement = domDocument.firstChildElement();
    QDomElement StatusInfoElement = DPProjectElement.firstChildElement("BasicInfo");
    QDomElement DataBaseElement = StatusInfoElement.firstChildElement("DataBaseFile");
    QDomText t = DataBaseElement.firstChild().toText();
    t.setData(newfile);
}
