#ifndef CSVFILE_H
#define CSVFILE_H
#include <QStringList>
#include <QVector>
#include <QIODevice>
#include <QTextStream>
#include <QFile>

class CsvFile
{
public:
    CsvFile(QString fullFileName);

    QString fullFileName;
    int actRowNum;
    int actColNum;

    QVector<QStringList> fileData;
};

#endif // CSVFILE_H
