#ifndef PROJECTDOM_H
#define PROJECTDOM_H

#include <QDomDocument>
#include <QAbstractItemModel>
//class DomItem;

class ProjectDom
{
public:
    ProjectDom(QDomDocument document, QObject *parent = 0);
    QDomDocument domDocument;
    QString projectName;
    QString projectDir;
    void    InitWriteXml();
    void    ProjectChanged();
    void    ProjectSaved();
    bool    ProjectNotSaved();
private:
    bool    flagNeedToSave;
};

#endif // PROJECTDOM_H

