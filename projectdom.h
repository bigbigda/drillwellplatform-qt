#ifndef PROJECTDOM_H
#define PROJECTDOM_H

#include <QDomDocument>
#include <QAbstractItemModel>

#include <excelfile.h>
#include <csvfile.h>
#include <excelfile.h>

struct TableInf{
    QString         tableName;
    QStringList     tableRowHeadTag;
    QStringList     tableConstData[5];
    int             tableColNum;
    int             tableRowNum;
};

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
    void    InitTableStruct();

    void    projectChanged();
    void    projectSaved();
    bool    showNotSaveFlag();

    ExcelFile * efilep[4];
    CsvFile   * cfilep[2];
    TableInf    tableinf[2];
private:
    bool    flagNeedToSave;
};

#endif // PROJECTDOM_H

