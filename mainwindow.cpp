#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <iostream>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent, QString init_worldmap )
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(init_worldmap));
    auto rect = scene->addRect(10, 50, 50, 120);
    rect->setZValue(1.1);
    rect->setFlag(QGraphicsItem::ItemIsMovable, true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

