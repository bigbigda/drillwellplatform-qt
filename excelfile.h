#ifndef ExcelFile_H
#define ExcelFile_H

#ifndef ZUANJUITEMNUM
#define ZUANJUITEMNUM 5
#endif

#include <QStringList>
#include <QString>
#include <QDebug>
#include <QAxObject>

class ExcelFile
{
public:
    ExcelFile(QString fileFullName, QString fileCategory, int rowNum, int colNum, int startRow, int startCol);

    bool readExcel(QAxObject *workbooks);
    bool checkExcel();

    QString fileFullName;           // 文件完整路径（含文件名）
    QString fileCategory;           //文件类型名
    int colNum;                     // 列数
    int rowNum;                     // 行数
    int startRow;
    int startCol;

    QVariantList variantListData;   //数据

    QStringList * fileStrList ;     //表各列名称
};

#endif // ExcelFile_H
