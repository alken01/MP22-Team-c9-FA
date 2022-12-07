#include "controller.h"
#include "graphicalview.h"
#include "mainwindow.h"
#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "textview.h"
#include "ui_mainwindow.h"
#include "world.h"
#include <iostream>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <Qt>
#include <QtGui>
#include <QTimer>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent, QString init_worldmap )
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(init_worldmap));

    // Create a text input field
    QLineEdit* textInput = new QLineEdit(this);

    // Create a button
    QPushButton* button = new QPushButton("Change View", this);

    // Create a vertical layout to arrange the widgets
    QVBoxLayout* layout = new QVBoxLayout;

    // Add the graphicsView and the text input field to the layout
    layout->addWidget(ui->graphicsView);
    layout->addWidget(textInput);

    // Set the layout for the main window
    this->setLayout(layout);

    // Add the button to the toolbar
//    ui->mainToolBar->addWidget(button);

    // Connect the button's clicked signal to the changeScene slot
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::changeScene()
{
    // Create a new scene
    QGraphicsScene* newScene = new QGraphicsScene(this);

    // Add an item to the scene
    newScene->addRect(QRectF(0, 0, 100, 100));

    // Set the new scene for the graphicsView
    ui->graphicsView->setScene(newScene);
}

