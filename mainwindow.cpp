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
#include "astar.h"



MainWindow::MainWindow(QWidget* parent, std::shared_ptr<Controller> c)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    this->controller = c;

    // Create a text input field
    textInput = ui->lineEdit;


    // Create a button
    QPushButton* button = ui->pushButton;

    //hide scrollbar terminal
    ui->textEdit_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //progressBar health
    health = ui->progressBar;
    health->setRange(0, 100);
    health->setValue(c->getWorld()->getProtagonist()->getHealth());

    //progressBar energy
    energy = ui->progressBar_2;
    energy->setRange(0, 100);
    energy->setValue(c->getWorld()->getProtagonist()->getEnergy());

    //autocomplete
    QCompleter* completer = new QCompleter(c->getCompleterList(), this);
    ui->lineEdit->setCompleter(completer);

    // Connect all
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
    connect(textInput, &QLineEdit::textChanged, this, &MainWindow::textEntered);
    connect(textInput, &QLineEdit::returnPressed, this, &MainWindow::pressEntered);

    //empty line edit after autocomplete
    QObject::connect(completer, SIGNAL(activated(const QString&)),
        ui->lineEdit, SLOT(clear()),
        Qt::QueuedConnection);
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

void MainWindow::initViews(){
    ui->verticalLayout_2->addWidget(controller->getQtext_view().get());
    ui->verticalLayout_2->addWidget(controller->getQgraphics_view().get());
    controller->getQgraphics_view().get()->hide();
}


void MainWindow::changeScene(){
    if(viewStatus == 1){
        controller->getQtext_view().get()->show();
        controller->getQgraphics_view().get()->hide();
        ui->lineEdit->show();
        viewStatus = 0;
    } else{
        controller->getQgraphics_view().get()->show();
        controller->getQtext_view().get()->hide();
        ui->lineEdit->hide();
        ui->textEdit_4->clear();
        viewStatus = 1;
    }
}

void MainWindow::pressEntered(){
    QString input = this->textInput->text();
    //updatePath(input);
    QString result = controller->commandReceived(input);
    if(result == "help"){
        auto s = controller->getCompleterList();
        ui->textEdit_4->append("--------------------------------");
        ui->textEdit_4->append("Possible commands:");
        for(int i = 0; i < s.length(); i++){
            ui->textEdit_4->append(s.at(i));
        }
        ui->textEdit_4->append("--------------------------------");
    }

    //maybe need to change this back
    //needs to be fixed somehow anyway
    else if(!result.isNull() || input.left(4) == "goto"){
        ui->textEdit_4->append(input);
    } else ui->textEdit_4->append("Unrecognized input - type 'help' for possible commands");

    //clear input
    textInput->clear();

    //update visualisations
    health->setValue(this->controller->getWorld()->getProtagonist()->getHealth());
    energy->setValue(this->controller->getWorld()->getProtagonist()->getEnergy());
    ui->lcdNumber->display(controller->getPoisoned());
}
void MainWindow::textEntered(){

}

void MainWindow::setController(std::shared_ptr<Controller>& c){
    this->controller = c;
}
