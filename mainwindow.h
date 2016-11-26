#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "excelfile.h"
#include "enterdata.h"

namespace Ui {
class MainWindow;
}
class QAction;
class QLabel;
class QMenu;
class CreateProWizard;
class ProjectDom;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MainWindow::closeEvent (QCloseEvent *event);

private:

private slots:

   // void open();
    void on_action_About_triggered();

    void on_action_Exit_triggered();

    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Cal_triggered();

    void on_action_LaF_triggered();

    void on_action_set_triggered();

    void on_action_ReadExcel_triggered();

    void on_action_EnterData_triggered();

private:
    Ui::MainWindow *ui;
    CreateProWizard *createprodialogPoint;
    ProjectDom * projectdompoint;
};

#endif // MAINWINDOW_H
