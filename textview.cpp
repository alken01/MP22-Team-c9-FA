#include "textview.h"
#include "world.h"
#include <iostream>

TextView::TextView()
{}


void TextView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView ){
    this->height=w->getHeight();
    this->width=w->getWidth();
    this->outputView=textView;
    std::cout.flush();
    std::cout << "height:" << this->height << "width:"<< this->width << std::endl;
    auto enemies=w->getEnemies();
    auto healthPacks=w->getHealthPacks();
    auto protagonist=w->getProtagonist();
    auto tiles=w->getTiles();
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

           auto temp=std::dynamic_pointer_cast<PEnemy>(enemies.at(i));

           if(temp != nullptr){
            changeSignAtCoord(x,y,'P');
            std::cout.flush();
            std::cout << "P enemy at Y:" << y << "X:"<< x <<"added" << std::endl;
           }
           else {
               changeSignAtCoord(x,y,'E');
           std::cout << "Normal enemy at Y:" << y << "X:"<< x <<"added" << std::endl;
           }
       }

       //add health
       for (unsigned long i = 0; i < healthPacks.size(); ++i) {
           int x =healthPacks.at(i)->getXPos();
           int y =healthPacks.at(i)->getYPos();
           changeSignAtCoord(x,y,'H');
           std::cout.flush();
           std::cout << "Health added at Y:" << y << "X:"<< x <<"added" << std::endl;

       }

       //add walls
       for (unsigned long i = 0; i < tiles.size(); ++i) {
           if(tiles.at(i)->getValue()==INFINITY){
               int x =tiles.at(i)->getXPos();
               int y =tiles.at(i)->getYPos();
               changeSignAtCoord(x,y,'@');
           }
       }

       //add prot
       unsigned long x= protagonist->getXPos();
       unsigned long y =protagonist->getYPos();
       changeSignAtCoord(x,y,'$');

       this->textscene->addText(*stringWorld,QFont("SF Mono"));
       textView->setScene(this->textscene);
}


// This code will be used in controller / changed so it gets input from controller
void TextView::movProtagonist(int x1, int y1, int x2, int y2){
    changeSignAtCoord(x1,y1,' ');
    changeSignAtCoord(x2,y2,'$');
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("SF Mono"));
}

void TextView::changeSignAtCoord( unsigned long x,  unsigned long y, QChar input){
    int rowlength = width*8+4;//(width*4+2)*2; one less multiplication
    int indexCount = rowlength*y-(width-x)*4-4;
    this->stringWorld->replace(indexCount, 1,input);
}

void TextView::updateView(){
    this->outputView->setScene(this->textscene);
}

void TextView::protDead(int x, int y){
    changeSignAtCoord(x,y,'D');
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("SF Mono"));

}


