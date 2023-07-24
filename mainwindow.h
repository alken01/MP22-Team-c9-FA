#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QComboBox>
#include <QCompleter>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollBar>
#include <QStringList>
#include <QTimer>
#include <QVBoxLayout>
#include <Qt>
#include <QtGui>
#include <iostream>
#include <memory>

#include "QtWidgets/qgraphicsview.h"
#include "controller.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
using namespace std;
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent, std::shared_ptr<Controller> c);
    ~MainWindow();
    void changeScene();
    void setController(std::shared_ptr<Controller>& c);
    void updateImage(int, QComboBox* comboBox, QLabel* label);
    void setScroll();
    void goToPath(int x, int y);
    void updatePath(QString input);
    void pressEntered();
    void initCamera();
    void initViews();
    vector<QString> pathToText(vector<pair<int, int>> path);

   private:
    Ui::MainWindow* ui;
    QLineEdit* textInput;
    std::shared_ptr<Controller> controller;
    QGraphicsView textView;
    QProgressBar *health, *energy;
    QCompleter* completer;
    int viewStatus;
    void textEntered();
    void mapChanged();
    void getFeedback();
    void setHeuristic();
    void autoplay();
    void changeSpeed();
};
#endif  // MAINWINDOW_H
