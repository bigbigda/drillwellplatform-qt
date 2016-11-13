#ifndef PROJECTDOM_H
#define PROJECTDOM_H

#include <QDomDocument>
#include <QAbstractItemModel>
//class DomItem;

class ProjectDom
{
public:
    ProjectDom(QDomDocument document);
    QDomDocument domDocument;
    QString projectName;
    QString projectDir;
    bool    projectIsrealtime;

    void    InitWriteXml();
    int     showKaiInfo();
    int     showCiInfo();
    QString  showStepSize();
    double  backStepSize();
    QString showDataBaseFile();
    void    setDataBaseFile(QString newfile);

    void    projectChanged();
    void    projectSaved();
    bool    showNotSaveFlag();
private:
    bool    flagNeedToSave;
};

#endif // PROJECTDOM_H

