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
#include <QScrollBar>


MainWindow::MainWindow(QWidget* parent, QString init_worldmap, std::shared_ptr<Controller> c)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->controller=c;
    //QGraphicsScene* scene = new QGraphicsScene(this);
    //ui->graphicsView->setScene(scene);
    //scene->addPixmap(QPixmap(init_worldmap));

    //ui -> graphicsGridLayout ->addWidget(c->get().get());

    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setScene((c->getQtext_view().get())->scene());

    // Create a text input field
    textInput = ui->lineEdit;
    textInput->setGeometry(QRect(QPoint(10, 575), QSize(400, 30)));


    // Create a button
    QPushButton* button = ui->pushButton;
    button->setGeometry(QRect(QPoint(900, 0), QSize(200, 50)));


    //progressBar health
    health = ui->progressBar;
    health->setRange(0,100);
    health->setValue(c->getWorld()->getProtagonist()->getHealth());

    //progressBar energy
    energy = ui->progressBar_2;
    energy->setRange(0,100);
    energy->setValue(c->getWorld()->getProtagonist()->getEnergy());

    // Connect the button's clicked signal to the changeScene slot
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
    connect(textInput, &QLineEdit::textChanged, this, &MainWindow::textEntered);

    scrollMarginY = this->controller->getWorld()->getHeight()/20;
    scrollMarginX=  this->controller->getWorld()->getWidth()/20;
    int ratio = scrollMarginX/scrollMarginY;
    scrollMarginY = scrollMarginY*ratio;
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
    QScrollBar* yPos=ui->graphicsView->verticalScrollBar();
    QScrollBar* xPos=ui->graphicsView->horizontalScrollBar();

    QString input = this->textInput->text();
    if(input == "u"){
        this->controller->movePlayer(4);
        this->textInput->clear();

        yPos->setValue(yPos->value()-this->scrollMarginY);
    }

    if(input == "d"){
        this->controller->movePlayer(1);
        this->textInput->clear();

        yPos->setValue(yPos->value()+this->scrollMarginY);
    }

    if(input == "l"){
        this->controller->movePlayer(3);
        this->textInput->clear();

        xPos->setValue(xPos->value()-this->scrollMarginX);
    }

    if(input == "r"){
        this->controller->movePlayer(2);
        this->textInput->clear();

        xPos->setValue(xPos->value()+this->scrollMarginX);

    }
    health->setValue(this->controller->getWorld()->getProtagonist()->getHealth());
    energy->setValue(this->controller->getWorld()->getProtagonist()->getEnergy());
}

void MainWindow::setController(std::shared_ptr<Controller>& c){
    this->controller = c;
}

void MainWindow::setScroll(){
    ui->graphicsView->verticalScrollBar()->setValue(0);
     ui->graphicsView->horizontalScrollBar()->setValue(0);
}
