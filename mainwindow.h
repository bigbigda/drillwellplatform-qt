#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>


namespace Ui {
class MainWindow;
}
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
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
     bool loadFile(const QString &);
     void setImage(const QImage &newImage);

private slots:

   // void open();
    void on_action_About_triggered();

    void on_action_Exit_triggered();

    void on_action_Save_triggered();

    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Cal_triggered();

    void on_pushButton2_clicked();

private:
    Ui::MainWindow *ui;
    QImage image;
    QLabel *imageLabel;
    double scaleFactor;
    CreateProWizard *createprodialogPoint;
    ProjectDom * projectdompoint;
};

#endif // MAINWINDOW_H
