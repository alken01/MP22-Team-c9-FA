#include "textview.h"
#include "qscrollbar.h"
#include "world.h"
#include <iostream>

TextView::TextView()
{
    //poison timer
    timer.setInterval(1000);
    toggle = 1;
}


void TextView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView ){
    this->height=w->getHeight();
    this->width=w->getWidth();
    this->outputView=textView;
    startposX=w->getProtagonist()->getXPos();
    startposY=w->getProtagonist()->getYPos();
    this->world=w;
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


       //cut world to size
       moveCamera();


       //couldn't make newline characters work when printing text seperately --> combine all first into single string
       this->stringWorld = std::make_shared<QString>();
       for (int i = 0; i < qVecPlayer.size(); ++i) {
           stringWorld->append(qVecPlayer.at(i));
       }


       this->textscene->addText(*stringWorld,QFont("Monospace"));
       textView->setScene(this->textscene);
       textView->setEnabled(true);

       //poison timer
       connect(&timer,&QTimer::timeout,this,&TextView::togglePoisoned);
}


// This code will be used in controller / changed so it gets input from controller
void TextView::movProtagonist(int x1, int y1, int x2, int y2){
    changeSignAtCoord(x1,y1,' ');
    changeSignAtCoord(x2,y2,'$');
    moveCamera();

    this->stringWorld = std::make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }

    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("Monospace"));
}

void TextView::changeSignAtCoord( unsigned long x,  unsigned long y, QChar input){
    qVec[(y)*4+2].replace(2+(x)*4, 1,input);
}

void TextView::updateView(){
    this->outputView->setScene(this->textscene);
}

void TextView::protDead(int x, int y){
    changeSignAtCoord(x,y,'D');
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("Monospace"));

}

//code for poison flashing
void TextView::togglePoisoned(){
    if(toggle==1){
        this->textscene->setBackgroundBrush(QColor("purple"));
        toggle=0;
    }
    else{
         this->textscene->setBackgroundBrush(QColor("base"));
         toggle=1;
    }
    timer.start();
}

void TextView::startTimer(){
    timer.start();
}

void TextView::stopTimer(){
    timer.stop();
    this->textscene->setBackgroundBrush(Qt::transparent);
}

void TextView::moveCamera(){
    //cut world to size
    QVector<QString> temp;
    qVecPlayer=qVec;
    qVecPlayer=qVecPlayer.mid((world->getProtagonist()->getYPos()-3)*4,30);

    for (int i = 0; i < qVecPlayer.size(); ++i) {
        temp.push_back(qVecPlayer[i].mid((world->getProtagonist()->getXPos()-6)*4,60));
    }
    qVecPlayer=temp;
}



