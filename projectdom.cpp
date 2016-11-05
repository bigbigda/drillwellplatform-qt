#include "projectdom.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

ProjectDom::ProjectDom(QDomDocument document,QObject *parent)
    :domDocument (document)
{
    ProjectSaved();
}

void ProjectDom::ProjectChanged()
{
    this->flagNeedToSave = true;
}

void ProjectDom::ProjectSaved()
{
    this->flagNeedToSave = false;
}

bool    ProjectDom::ProjectNotSaved()
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
