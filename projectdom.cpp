#include "projectdom.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

ProjectDom::ProjectDom(QDomDocument document)
    :domDocument (document)
{
    projectSaved();
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
