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
    QVector <QStringList> fileData;

    int             tableColNum;
    int             tableRowNum;
};

struct KaiCiNum{
    int     kainum;
    int     cinum;
};

struct LineData{
    QString     kaiLineD0;
    QString     kaiLineD1;
    QString     kaiLineD2;
    QString     kaiLineD3;
    QString     kaiLineD4;
    QString     kaiLineD5;
    QString     kaiLineD6;

    QString     ciLineD0;
    QString     ciLineD1;
    QString     ciLineD2;
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
    KaiCiNum    showStartKaiCiNum();
    void        setStartKaiCiNum(KaiCiNum kaicinum);
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
    CsvFile   * cfilep[3];
    TableInf    tableinf[2];
    KaiCiNum    tmpKaiCiNum;
    LineData    tmpLineData;

private:
    bool    flagNeedToSave;
};

#endif // PROJECTDOM_H

