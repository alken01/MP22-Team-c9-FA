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
#include "astar.h"#include <QtGui>



MainWindow::MainWindow(QWidget* parent, QString init_worldmap, std::shared_ptr<Controller> c)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->controller=c;
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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



    //textview scrolling
    scrollMarginY = this->controller->getWorld()->getHeight()/15;
    scrollMarginX=  this->controller->getWorld()->getWidth()/15;
    int ratio = scrollMarginX/scrollMarginY;
    scrollMarginY = scrollMarginY*ratio;


    // Connect all
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
    connect(textInput, &QLineEdit::textChanged, this, &MainWindow::textEntered);
    connect(textInput, &QLineEdit::returnPressed, this, &MainWindow::pressEntered);

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

void MainWindow::goToPath(int x, int y){
    auto w = this->controller->getWorld();
    Tile start(w->getProtagonist()->getXPos(),w->getProtagonist()->getYPos(),0.0);
    Tile end(x,y,0.0);
    vector<pair<int, int> > path = astar(w->getTiles(), w->getHeight(), w->getWidth(), start, end, 0.1);
    vector<QString> textPath = pathToText(path);
    for (const auto& input : textPath) {
        updatePath(input);
        cout<< "moving" << input.toStdString() <<endl;
    }
}

vector<QString> MainWindow::pathToText(vector<pair<int, int> > path){
    // Resulting vector of directions
    std::vector<QString> directions;

    // Loop through the path and convert each pair of coordinates into a direction
    for (size_t i = 1; i < path.size(); i++)
    {
        // Get the current and previous coordinates
        auto current = path[i];
        auto prev = path[i - 1];

        // Compare the coordinates and add the corresponding direction to the result vector
        if (current.first > prev.first){
            directions.push_back(QString("r"));
        }
        else if (current.first < prev.first){
            directions.push_back(QString("l"));
        }
        else if (current.second > prev.second){
            directions.push_back(QString("d"));
        }
        else if (current.second < prev.second){
            directions.push_back(QString("u"));
        }
    }

    // Return the vector of directions
    return directions;
}

void MainWindow::textEntered(){
    QString input = this->textInput->text();
    updatePath(input);
}

void MainWindow::pressEntered(){
    QString input = this->textInput->text();

    if (input.at(0) == 'g'){
        QStringList strList = input.split(" ");

        QString strY = strList.last();  // gets the last substring
        strList.removeLast();           // removes the last item from the list
        QString strX = strList.last();  // gets the second-to-last substring

        bool ok;
        int x = strX.toInt(&ok);        // convert the QString to an int, store the result in x
        if (!ok) {
            qDebug() << "Error converting string to int";
            return;
        }

        int y = strY.toInt(&ok);
        if (!ok) {
            qDebug() << "Error converting string to int";
            return;
        }

        goToPath(x,y); //call the helper function
    }
    this->textInput->clear();
}

void MainWindow::updatePath(QString input){
    QScrollBar* yPos=ui->graphicsView->verticalScrollBar();
    QScrollBar* xPos=ui->graphicsView->horizontalScrollBar();

    if(input == "u"){
        this->controller->movePlayer(4);
        this->textInput->clear();

        yPos->setValue(yPos->value()-this->scrollMarginY);
    }

    else if(input == "d"){
        this->controller->movePlayer(1);
        this->textInput->clear();

        yPos->setValue(yPos->value()+this->scrollMarginY);
    }

    else if(input == "l"){
        this->controller->movePlayer(3);
        this->textInput->clear();

        xPos->setValue(xPos->value()-this->scrollMarginX);
    }

    else if(input == "r"){
        this->controller->movePlayer(2);
        this->textInput->clear();

        xPos->setValue(xPos->value()+this->scrollMarginX);

    }
    health->setValue(this->controller->getWorld()->getProtagonist()->getHealth());
    energy->setValue(this->controller->getWorld()->getProtagonist()->getEnergy());
    //poisoned steps visualisation
    ui->lcdNumber->display(controller->getPoisoned());
}


void MainWindow::setController(std::shared_ptr<Controller>& c){
    this->controller = c;
}

void MainWindow::setScroll(){
    ui->graphicsView->verticalScrollBar()->setValue(0);
    ui->graphicsView->horizontalScrollBar()->setValue(0);
}



