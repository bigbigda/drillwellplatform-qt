#ifndef CREATEPRODIALOG_H
#define CREATEPRODIALOG_H

#include <QDialog>
#include "projectdom.h"

namespace Ui {
class CreateProDialog;
}

class CreateProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProDialog(const QString  dir, ProjectDom * tmpdompoint ,QWidget *parent = 0);
    ~CreateProDialog();
    QString BackProjectName();
    QString BackProjectDir();
    void        CreateQDom();
    ProjectDom * projectdompoint;
private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::CreateProDialog *ui;
};

#endif // CREATEPRODIALOG_H
