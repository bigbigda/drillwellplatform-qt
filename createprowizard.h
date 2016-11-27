#ifndef CREATEPRODIALOG_H
#define CREATEPRODIALOG_H

#include <QWizard>
#include <QFileDialog>
#include <QDate>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QValidator>
#include <QCoreApplication>

#include "projectdom.h"

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;

class CreateProWizard :  public QWizard
{
    Q_OBJECT

public:

    enum {Page_Start, Page_Real, Page_Esti, Page_End};

    CreateProWizard(ProjectDom * tmpdompoint ,QWidget *parent = 0);
    ~CreateProWizard();

    void        CreateQDom();
    ProjectDom * projectdompoint;

    void accept() Q_DECL_OVERRIDE;

private:

};

class CreateProPage : public QWizardPage
{
    Q_OBJECT

public:
    CreateProPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;
private slots:
        void browse();
private:
    QLabel *label;
    QLabel *proNameLabel;
    QLineEdit *proNameLineEdit;
    QLabel *label2;
    QLabel *proDirLabel;
    QLineEdit *proDirLineEdit;
 //   QComboBox *proDirLineEdit;
    QRadioButton *realtimeProRadioButton;
    QRadioButton *estimateProRadioButton;
    QGroupBox *groupBox;
    QPushButton *browseButton;
};

class KaiCiPage : public QWizardPage
{
    Q_OBJECT
public:
    KaiCiPage(QWidget *parent = 0);
    int nextId() const Q_DECL_OVERRIDE;
private:
    QRadioButton *fromnewRadioButton;
    QRadioButton *fromotherRadioButton;

    QLabel * KaiLabel;
    QLineEdit * KaiLineEdit;
    QLabel * CiLabel;
    QLineEdit * CiLineEdit;


};

class EstimitPage : public QWizardPage
{
    Q_OBJECT
public:
    EstimitPage(QWidget *parent = 0);
private:
    QRadioButton *HasDetailRadioButton;
    QRadioButton *DontHasDetailRadioButton;
    QGroupBox *groupBox;

    QLabel * TaoFLabel;
    QLineEdit * TaoFLineEdit;
    QLabel * LuoFLabel;
    QLineEdit * LuoFLineEdit;


};
class ProInfoPage : public QWizardPage
{
    Q_OBJECT

public:
    ProInfoPage(QWidget *parent = 0);


private:
    QLabel    * wellNameLabel;
    QLineEdit * wellNameLineEdit;
    QLabel    * projectStepSizeLabel;
    QLineEdit * projectStepLineEdit;
    QLabel    * wellXingLabel;
    QLineEdit * wellXingLineEdit;
    QLabel    * wellBieLabel;
    QLineEdit * wellBieLineEdit;
    QLabel *wellDepthLabel;
    QLineEdit *wellDepthLineEdit;


};
#endif // CREATEPRODIALOG_H
