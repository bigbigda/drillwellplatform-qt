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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
     bool loadFile(const QString &);
     void setImage(const QImage &newImage);

private slots:
    void on_action1_triggered();
   // void open();
    void on_actionA_triggered();

    void on_actionA_2_triggered();

private:
    Ui::MainWindow *ui;
    QImage image;
    QLabel *imageLabel;
    double scaleFactor;

};

#endif // MAINWINDOW_H
