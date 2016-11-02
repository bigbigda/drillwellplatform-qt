#ifndef CREATEPRODIALOG_H
#define CREATEPRODIALOG_H

#include <QDialog>

namespace Ui {
class CreateProDialog;
}

class CreateProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProDialog(const QString  dir, QWidget *parent = 0);
    ~CreateProDialog();
    QString BackProjectName();
    QString BackProjectDir();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

private:
    Ui::CreateProDialog *ui;
};

#endif // CREATEPRODIALOG_H
