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
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <Qt>
#include <QtGui>
#include <QTimer>
#include <QVBoxLayout>
#include "controller.h"
#include "world.h"
#include "graphicalview.h"
#include "textview.h"


MainWindow::MainWindow(QWidget* parent, QString init_worldmap)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(init_worldmap));


    // Create a text input field
    textInput = new QLineEdit(this);
    textInput->setGeometry(QRect(QPoint(10, 575), QSize(400, 30)));

    //commit text button
    QPushButton* textButton = new QPushButton("Enter", this);
    textButton->setGeometry(QRect(QPoint(420, 575), QSize(200, 50)));

    // Create a button
    QPushButton* button = new QPushButton("Change View", this);
    button->setGeometry(QRect(QPoint(900, 0), QSize(200, 50)));

    // Connect the button's clicked signal to the changeScene slot
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
    connect(textInput, &QLineEdit::textChanged, this, &MainWindow::textEntered);
}

class ImageAndSelector
{
    Q_OBJECT

public:
    // Constructor
    ImageAndSelector();

    // Other member functions
    QComboBox* getQcomboBox(){
        return comboBox;
    }
    QLabel* getQLabel(){
        return label;
    }

    void setQcomboBox(QComboBox* newCombo){
        comboBox = newCombo;
    }

    void setQLabel(QLabel* newLabel){
        label = newLabel;
    }

    // Slot function
    Q_SLOT void updateImage(int index){

        // Get the selected item from the QComboBox
        QString selectedItem = comboBox->itemText(index);

        // Create a QPixmap object with the selected item's image path
        QPixmap pixmap(selectedItem);

        // Set the QLabel's pixmap to the QPixmap object
        label->setPixmap(pixmap);
    }

private:
    // Private member variables
    QComboBox* comboBox;
    QLabel* label;
};

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::changeScene(){
    // Create a new scene
    QGraphicsScene* newScene = new QGraphicsScene(this);

    // Add an item to the scene
    newScene->addRect(QRectF(0, 0, 100, 100));

    // Set the new scene for the graphicsView
    ui->graphicsView->setScene(newScene);
}

void MainWindow::textEntered(){
    QString input = this->textInput->text();
    if(input == "up"){
        this->controller->movePlayer("up");
        this->textInput->clear();
    }

    if(input == "down"){
        this->controller->movePlayer("down");
        this->textInput->clear();
    }

    if(input == "left"){
        this->controller->movePlayer("left");
        this->textInput->clear();
    }

    if(input == "right"){
        this->controller->movePlayer("right");
        this->textInput->clear();
    }
}

void MainWindow::setController(std::shared_ptr<Controller>& c){
    this->controller = c;
}
