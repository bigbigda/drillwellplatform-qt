#ifndef CALCWIZARD_H
#define CALCWIZARD_H
#include <QWizard>
#include <QtWidgets>
#include "projectdom.h"

class CalcWizard : public QWizard
{
public:
    CalcWizard(ProjectDom * tmpprodompoint);
    ProjectDom * projectdompoint;
};

class SetStepPage : public QWizardPage
{
    Q_OBJECT

public:
    SetStepPage(ProjectDom * tmpprodompoint,QWidget *parent = 0);
    ProjectDom * projectdompoint;
private:
    QLabel      * pronameLabel;
    QLabel      * pronameLabel2;
    QLabel      * procatLabel;
    QLabel      * procatLabel2;
    QLabel      * setstepLabel;
    QLineEdit   * setstepLineEdit;

};

class ShowAndEditDialog : public QDialog
{
    Q_OBJECT
public:
    ShowAndEditDialog(ProjectDom * tmpprodompoint, QWidget *parent = 0);
    ProjectDom * projectdompoint;
private:

};

class NiuFPage : public QWizardPage
{
    Q_OBJECT

public:
    NiuFPage(ProjectDom * tmpprodompoint, QWizard *parent = 0);
    QWizard * parentwizardpoint;
    ProjectDom * projectdompoint;
bool NiuFPage::isComplete()const;
private slots:
    void on_fricforcButton_clicked();
    void on_torquecalcButton_clicked();
    void on_calcbutton_clicked();
private:
    QPushButton *fricforcButton;
    QPushButton *torquecalcButton;
    QPushButton * calcbutton;
    ShowAndEditDialog * showandeditdialog;
};


#endif // CALCWIZARD_H
