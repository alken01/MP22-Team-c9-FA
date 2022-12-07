#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QString init_worldmap = ":/images/world_images/maze1.png");
    ~MainWindow();
    void changeScene();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
