#ifndef ENTERDATA_H
#define ENTERDATA_H
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLineEdit>
#include "QPushButton"
#include <QGroupBox>
#include <projectdom.h>

class EnterData : public QDialog
{
    Q_OBJECT
public:
    EnterData(ProjectDom * tmpdompoint ,QWidget *parent = 0);
    void browse();
    void addLineData();

    QGridLayout *   KaiLayout;
    QGridLayout *   CiLayout;

    QVBoxLayout *   layout;
    QLineEdit   *   readzjDbLineEdit;
    ProjectDom  *   projectdompoint;
    QLineEdit *     KaiD0Edit;
    QLineEdit *     KaiD1Edit;
    QLineEdit *     KaiD2Edit;
    QLineEdit *     KaiD3Edit;
    QLineEdit *     KaiD4Edit;
    QLineEdit *     KaiD5Edit;
    QLineEdit *     KaiD6Edit;
    QLineEdit *     CiD0Edit;
    QLineEdit *     CiD1Edit;
    QLineEdit *     CiD2Edit;

    QLabel       * timeInfoLabel;
    QRadioButton * newKaiButton;
    QRadioButton * newCiButton;
    QPushButton  * confirmNewButton;
private slots:
    void    selKaiCi();
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
    void searchSlot();
    void addSearchItemSlot();
    void removeRowSlot();
};
#endif // ENTERDATA_H
