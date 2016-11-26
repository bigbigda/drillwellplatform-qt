#include "csvfile.h"


CsvFile::CsvFile(QString fullFileName)
{
    this->fullFileName = fullFileName;
    QFile csv_file(fullFileName);

    if (csv_file.open(QIODevice::ReadOnly)) {
        QTextStream in(&csv_file);

        while (!in.atEnd()) {

            QString fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",");
            //ignore commented lines
            if(lineToken.size() > 1){
                for (int j = 0; j < lineToken.size(); j++) {
                    QString value = lineToken.at(j);
                    if(j == 0){
                        fileData.append(QStringList());
                    }
                    if(fileData.count() > 0)
                        fileData[fileData.count() - 1].append(value);
                }
            }
        }
        actRowNum = fileData.size();
        actColNum = fileData[0].size();
        csv_file.close();
    }
}
