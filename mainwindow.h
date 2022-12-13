#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "controller.h"
#include <QLabel>
#include <QComboBox>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent, QString init_worldmap, std::shared_ptr<Controller> c);
    ~MainWindow();
    void changeScene();
    void setController(std::shared_ptr<Controller>& c);
    void updateImage(int, QComboBox* comboBox, QLabel* label);
    void setScroll();
    void goToPath(int x, int y);
    vector<QString> pathToText(vector<pair<int, int> > path);
    void updatePath(QString input);

private:
    Ui::MainWindow* ui;
    QLineEdit* textInput;
    void textEntered();
    std::shared_ptr<Controller> controller;
    QGraphicsView textView;
    QProgressBar* health, * energy;
    int scrollMarginY;
    int scrollMarginX;
};
#endif // MAINWINDOW_H
