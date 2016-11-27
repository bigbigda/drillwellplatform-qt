#ifndef PROJECTDOM_H
#define PROJECTDOM_H

#include <QDomDocument>
#include <QAbstractItemModel>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>


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

struct KaiCiNum{
    int     kainum;
    int     cinum;
};

class ProjectDom
{
public:
    ProjectDom();
    ~ProjectDom();
    QDomDocument domDocument;
    QString projectName;
    QString projectDir;
    bool    projectIsrealtime;

    void        InitWriteXml();
    int         showKaiInfo();
    int         showCiInfo();
    QString     showStepSize();
    double      backStepSize();
    QString     showDataBaseFile();
    void        setDataBaseFile(QString newfile);
    void        InitTableStruct();

    KaiCiNum    showKaiCiNum();
    void        setKaiCiNum(KaiCiNum kaicinum);
    bool        showHasFinishFirst();
    void        setHasFinishFirst();

    bool        showHasDetail();
    QString     showTaomo();
    QString     showLuomo();
    void        setLuomo(QString luomo);

    void        projectChanged();
    void        projectSaved();
    bool        showNotSaveFlag();

    ExcelFile * efilep[4];
    CsvFile   * cfilep[2];
    TableInf    tableinf[2];
private:
    bool    flagNeedToSave;
};

#endif // PROJECTDOM_H

