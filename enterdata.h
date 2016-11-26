#ifndef ENTERDATA_H
#define ENTERDATA_H
#include <QDialog>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QTableWidget>
#include<QLabel>
#include<QComboBox>
#include <qtablewidget.h>
#include <QHeaderView>
#include <projectdom.h>
#include<QFileDialog>
#include <QRadioButton>
#include<QButtonGroup>

class EnterData : public QDialog
{
public:
    EnterData(ProjectDom * tmpdompoint ,QWidget *parent = 0);
    void browse();

    QVBoxLayout * layout;
    QLineEdit * readzjDbLineEdit;
    ProjectDom   *  projectdompoint;
};



class tableVLayout : public QVBoxLayout
{
    Q_OBJECT
public:
    tableVLayout(ProjectDom *tmpdompoint, int type);

    QTableWidget *  inTableWidget;
    ProjectDom   *  projectdompoint;
    QComboBox    *  comboxArray[5];
    int             tabletype;

private slots:
    void addRowSlot();
    void removeRowSlot();
};
#endif // ENTERDATA_H
