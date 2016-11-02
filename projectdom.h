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
private:

};

#endif // PROJECTDOM_H

