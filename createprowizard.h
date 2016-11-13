#ifndef CREATEPRODIALOG_H
#define CREATEPRODIALOG_H

#include <QWizard>
#include "projectdom.h"
#include <QtWidgets>

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;

class CreateProWizard :  public QWizard
{
    Q_OBJECT

public:
    explicit CreateProWizard(ProjectDom * tmpdompoint ,QWidget *parent = 0);
    ~CreateProWizard();
    QString BackProjectName();
    QString BackProjectDir();
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
