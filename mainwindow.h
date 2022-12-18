#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "controller.h"
#include <QLabel>
#include <QComboBox>
#include <QProgressBar>
#include <QTimer>
#include <QLCDNumber>
#include <QStringList>
#include <QCompleter>
#include <memory>
#include "QtWidgets/qgraphicsview.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <Qt>
#include <QtGui>
#include <QTimer>
#include <QVBoxLayout>
#include "controller.h"
#include <QScrollBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent,std::shared_ptr<Controller> c);
    ~MainWindow();
    void changeScene();
    void setController(std::shared_ptr<Controller>& c);
    void updateImage(int, QComboBox* comboBox, QLabel* label);
    void setScroll();
    void goToPath(int x, int y);
    vector<QString> pathToText(vector<pair<int, int> > path);
    void updatePath(QString input);
    void pressEntered();
    void initCamera();
    void initViews();

private:
    Ui::MainWindow* ui;
    QLineEdit* textInput;
    void textEntered();
    std::shared_ptr<Controller> controller;
    QGraphicsView textView;
    QProgressBar* health, * energy;
    int viewStatus;
    void mapChanged();
    void getFeedback();
    void setHeuristic();
    void autoplay();
     QCompleter* completer;
     void changeSpeed();
};
#endif // MAINWINDOW_H
