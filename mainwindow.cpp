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

    void setQcomboBox(QComboBox *newCombo){
        comboBox = newCombo;
    }

    void setQLabel(QLabel *newLabel){
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
    QComboBox *comboBox;
    QLabel *label;
};

MainWindow::~MainWindow()
{
    delete ui;
}

