#include "excelfile.h"
#include <QMessageBox>

ExcelFile::ExcelFile(QString fileFullName, QString fileCategory, int rowNum, int colNum, int startRow, int startCol)
{
    this->fileFullName = fileFullName;
    this->fileCategory = fileCategory;
    this->rowNum = rowNum;
    this->colNum = colNum;
    this->startRow = startRow;
    this->startCol = startCol;

//    qDebug()<<fileName<<"> startRow "<<startRow<<"startCol "<<startCol;
}

bool ExcelFile::readExcel(QAxObject * workbooks)
{
    if(!workbooks){
        return false;
    }
    QAxObject*  workbook = workbooks->querySubObject("Open(const QString&)", fileFullName);
    if(!workbook){
        return false;
    }
    QAxObject* sheets = workbook->querySubObject("WorkSheets");
    QAxObject* sheet = sheets->querySubObject( "Item( int )", 1 );

    QAxObject * usedrange = sheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");

    rowNum = rows->property("Count").toInt();
    QVariant var = usedrange->dynamicCall("Value");
    workbook->dynamicCall("Close()");

    variantListData = var.toList();
    if(variantListData.isEmpty())
    {
        return false;
    }
    return true;
}

bool ExcelFile::checkExcel()
{
    QVariant tmpRow = variantListData.first();
    double tmpdata1 = tmpRow.toList().first().toDouble();
    double tmpdata2;

    for (int i = startRow ; i < rowNum ; i ++)
    {
        tmpdata2 = variantListData.at(i).toList().first().toDouble();
        if(tmpdata1 > tmpdata2)
        {
                return false;
        }
        tmpdata1 = tmpdata2;
    }
    return true;
}


