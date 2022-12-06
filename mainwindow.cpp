#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <iostream>
#include <QtGui>
#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "mainwindow.h"
#include "world.h"
#include "controller.h"
#include "graphicalview.h"
#include "textview.h"

MainWindow::MainWindow(QWidget *parent, QString init_worldmap )
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 5,5,0.25);
    auto gview = std::make_shared<GraphicalView>();
    auto tview = std::make_shared<TextView>();
    Controller* controller = new Controller(test,gview,tview);
    controller->switchToGraphic();
//    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(controller->getScene());
//    scene->addPixmap(QPixmap(init_worldmap));
//    auto rect = scene->addRect(10, 50, 50, 120);
//    rect->setZValue(1.1);
//    rect->setFlag(QGraphicsItem::ItemIsMovable, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

