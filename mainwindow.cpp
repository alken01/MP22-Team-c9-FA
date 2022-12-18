#include "controller.h"
#include "mainwindow.h"
#include "QtWidgets/qgraphicsview.h"
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
#include <QScrollBar>




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
    completer = new QCompleter(c->getCompleterList(), this);
    ui->lineEdit->setCompleter(completer);

    //mapSelector
    ui->comboBox->addItems(controller->getMapList());

    //heurstic slider
    controller->setWhiteValue(ui->heuristicSlider->value()/10);

    // Connect all
    connect(button, &QPushButton::clicked, this, &MainWindow::changeScene);
    connect(textInput, &QLineEdit::textChanged, this, &MainWindow::textEntered);
    connect(textInput, &QLineEdit::returnPressed, this, &MainWindow::pressEntered);
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &MainWindow::mapChanged);
    connect(ui->heuristicSlider, &QSlider::sliderMoved, this, &MainWindow::setHeuristic);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::autoplay);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::mapChanged);
    connect(ui->animationSlider, &QSlider::sliderMoved, this, &MainWindow::changeSpeed);

    //empty line edit after autocomplete
    QObject::connect(completer, SIGNAL(activated(const QString&)),
        ui->lineEdit, SLOT(clear()),
        Qt::QueuedConnection);

    //hide graphicsview stuff
    ui->zoomSlider->hide();
    ui->textEdit_11->hide();
    ui->pushButton_2->hide();

    ui->comboBox->setCurrentIndex(0);
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
    if(viewStatus == 1){ //textview
        controller->getQtext_view().get()->show();
        controller->getQgraphics_view().get()->hide();
        ui->lineEdit->show();
        ui->zoomSlider->hide();
        ui->textEdit_11->hide();
        viewStatus = 0;
    } else{ //graphicsView
        controller->getQgraphics_view().get()->show();
        controller->getQtext_view().get()->hide();
        ui->zoomSlider->show();
        ui->textEdit_11->show();
        ui->lineEdit->hide();
        ui->textEdit_4->clear();
        viewStatus = 1;
    }
}

void MainWindow::pressEntered(){
    if(controller->getWin() == 1){
        ui->textEdit_4->setText("You win!");
        ui->pushButton->hide();
        ui->pushButton_2->show();
        return;
    }
    if(controller->getAlive() != 1){
        ui->textEdit_4->setText("Player died - press restart button");
        ui->pushButton->hide();
        ui->pushButton_2->show();
        return;
    }
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
        ui->textEdit_4->append(result);
        getFeedback();
    } else ui->textEdit_4->append("Unrecognized input - type 'help' for possible commands");

    //clear input
    textInput->clear();

    //getfeedback if textview
    getFeedback();

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

void MainWindow::mapChanged(){
    controller->changeMap(ui->comboBox->currentText());
    //update visualisations
    health->setValue(this->controller->getWorld()->getProtagonist()->getHealth());
    energy->setValue(this->controller->getWorld()->getProtagonist()->getEnergy());
    ui->lcdNumber->display(controller->getPoisoned());
    ui->textEdit_4->clear();
    ui->pushButton_2->hide();
    ui->pushButton->show();

    //empty line edit after autocomplete
    QObject::connect(completer, SIGNAL(activated(const QString&)),
        ui->lineEdit, SLOT(clear()),
        Qt::QueuedConnection);
}

//get terminal message from controller
void MainWindow::getFeedback(){
    auto message = controller->getTerminalOut();
    if(message.isNull()) return;
    ui->textEdit_4->append(message);
    controller->setTerminalOut(NULL);
}

void MainWindow::setHeuristic(){
    controller->setWhiteValue(ui->heuristicSlider->value()/10);
}

void MainWindow::autoplay(){
    controller->autoPlay();
}

void MainWindow::changeSpeed(){
    controller->setAnimationSpeed(ui->animationSlider->value()*10);
}
