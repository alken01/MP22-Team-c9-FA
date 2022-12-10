#include "textview.h"
#include "world.h"
#include <iostream>

TextView::TextView()
{}


void TextView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView ){

    this->height=w->getHeight();
    this->width=w->getWidth();
    auto enemies=w->getEnemies();
    auto healthPacks=w->getHealthPacks();
    auto protagonist=w->getProtagonist();
    this->textscene =new QGraphicsScene();
    //Qstring = stores a string of 16-bit QChars --> implicit sharing: reduce memory usage and to avoid the needless copying of data
    auto wi = QString("+"); //Create Qstring for width
    auto h = QString("|"); //Create Qstring for height

    //for each column +---+ x width
       for(int i = 0; i < width; i++){
           wi.append("---+");
       }
       //for each column |   | x width
       for(int i = 0; i < width; i++){
           h.append("   |");
       }

       //for each row repeat shape x height
       for(int q = 0; q < height; q++){
           qVec.push_back(wi);
           qVec.append("\n");
           qVec.push_back(h);
           qVec.append("\n");
       }

       //close map bottom line
       qVec.push_back(wi);

       //couldn't make newline characters work when printing text seperately --> combine all first into single string
       this->stringWorld = std::make_shared<QString>();
       for (int i = 0; i < qVec.size(); ++i) {
           stringWorld->append(qVec.at(i));
       }

       //add enemies
       for (unsigned long i = 0; i <enemies.size(); ++i) {
           unsigned long x = enemies.at(i)->getXPos();
           unsigned long y = enemies.at(i)->getYPos();
           changeSignAtCoord(x,y,'E');
       }

       //add health
       for (unsigned long i = 0; i < healthPacks.size(); ++i) {
           int x =healthPacks.at(i)->getXPos();
           int y =healthPacks.at(i)->getYPos();
           changeSignAtCoord(x,y,'H');
       }

       //add prot
       unsigned long x= protagonist->getXPos();
       unsigned long y =protagonist->getYPos();
       changeSignAtCoord(x,y,'$');

       this->textscene->addText(*stringWorld,QFont("Monospace"));
       textView->setScene(this->textscene);
}


// This code will be used in controller / changed so it gets input from controller
void TextView::movProtagonist(int x1, int y1, int x2, int y2){
    changeSignAtCoord(x1,y1,' ');
    changeSignAtCoord(x2,y2,'$');
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("Monospace"));
}

void TextView::changeSignAtCoord( unsigned long x,  unsigned long y, QChar input){
    int rowlength = (width*4+2)*2;
    int indexCount = rowlength*y-(width-x)*4-4;
    this->stringWorld->replace(indexCount, 1,input);
}

void TextView::updateView(std::shared_ptr<QGraphicsView> textView){
    textView->setScene(this->textscene);
}

