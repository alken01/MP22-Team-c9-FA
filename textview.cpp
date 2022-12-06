#include "textview.h"
#include "world.h"
#include <iostream>

TextView::TextView()
{}



//void TextView::initTextView(std::shared_ptr<QGraphicsScene> sc, std::shared_ptr<World> wo){
//    this->width = wo->getCols();
//    this->height = wo->getRows();
//    this->sc = sc;
//    this->qVec.clear();
//    this->world = wo;
//    this->enemies = wo->getEnemies();
//    this->healthPacks = wo->getHealthPacks();
//    this->protagonist = wo->getProtagonist();
//}

void TextView::draw(int width,int height,std::unique_ptr<Tile> protagonist,std::vector<std::unique_ptr<Enemy>> enemies,std::vector<std::unique_ptr<Tile>> healthPacks,std::shared_ptr<QGraphicsScene> scene){

    //Qstring = stores a string of 16-bit QChars --> implicit sharing: reduce memory usage and to avoid the needless copying of data
    auto w = QString("+"); //Create Qstring for width
    auto h = QString("|"); //Create Qstring for height

    //for each column +---+ x width
       for(int i = 0; i < width; i++){
           w.append("---+");
       }
       //for each column |   | x width
       for(int i = 0; i < width; i++){
           h.append("   |");
       }

       //for each row repeat shape x height
       for(int q = 0; q < height; q++){
           qVec.push_back(w);
           qVec.append("\n");
           qVec.push_back(h);
           qVec.append("\n");
       }
       //close map bottom line
       qVec.push_back(w);

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
       unsigned long y = protagonist->getYPos();
       changeSignAtCoord(x,y,'$');

       this->sc->addText(*stringWorld,QFont("Monospace"));
}


// This code will be used in controller / changed so it gets input from controller
void TextView::movProtagonist(){
     unsigned long x= protagonist->getXPos();
     unsigned long y = protagonist->getYPos();
    changeSignAtCoord(x,y,'$');
    sc->clear();
    sc->addText(*stringWorld,QFont("Monospace"));
}

void TextView::changeSignAtCoord( unsigned long x,  unsigned long y, QChar input){
    int rowlength = (width*4+2)*2;
    int indexCount = rowlength*y-(width-x)*4-4;
    this->stringWorld->replace(indexCount, 1,input);
}


