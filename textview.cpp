#include "textview.h"
#include "qscrollbar.h"
#include "world.h"
#include <iostream>

TextView::TextView(){
    //poison timer
    timer.setInterval(1000);
    toggle = 1;
    
    timer2.setInterval(1000);
    timer2.isSingleShot();
}


void TextView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView ){
    this->height=w->getHeight();
    this->width=w->getWidth();
    this->outputView=textView;
    startposX=w->getProtagonist()->getXPos();
    startposY=w->getProtagonist()->getYPos();
    this->world=w;
    std::cout.flush();
    std::cout << "height:" << this->height << "width:" << this->width << std::endl;
    auto enemies = w->getEnemies();
    auto healthPacks = w->getHealthPacks();
    auto protagonist = w->getProtagonist();
    auto tiles = w->getTiles();
    this->textscene = new QGraphicsScene();
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
        //qVec.append("\n");
        qVec.push_back(h);
        //qVec.append("\n");
    }
    
    //close map bottom line
    qVec.push_back(wi);
    //add walls
    for (unsigned long i = 0; i < tiles.size(); ++i) {
        int x =tiles.at(i)->getXPos();
        int y =tiles.at(i)->getYPos();
        changeSignAtCoord(x,y,grayscaleToASCII(tiles.at(i)->getValue()));
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
    
    
    this->textscene->addText(*stringWorld,QFont("SF Mono"));
    textView->setScene(this->textscene);
    
    //poison timer
    connect(&timer,&QTimer::timeout,this,&TextView::togglePoisoned);
    
    //health timer
    connect(&timer2,&QTimer::timeout,this,&TextView::resetBg);
}

QChar TextView::grayscaleToASCII(float intensity){
    if(intensity == INFINITY){
        return QChar('@');
    }
    if(intensity <0.5){
        return QChar(' ');
    }
    std::vector<char> characters = {'.',':','-','=','+','*','#','%'};
    // scale the intensity value to the range of the character set and round it to the nearest index
    int index = round((intensity-0.49)* (characters.size() - 1));

    return QChar(characters[index]);
}


// This code will be used in controller / changed so it gets input from controller
void TextView::movProtagonist(int x1, int y1, int x2, int y2,std::shared_ptr<WorldModel> w){
    int i = y1 * w->getWidth()+ x1;
    auto tiles = w->getTiles();
    changeSignAtCoord(x1,y1,grayscaleToASCII(tiles.at(i)->getValue()));
    changeSignAtCoord(x2,y2,'$');
    moveCamera();
    
    this->stringWorld = std::make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }
    
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("SF Mono"));
}

void TextView::changeSignAtCoord( unsigned long x,  unsigned long y, QChar input){
    qVec[y*2+1].replace(2+x*4, 1,input);
    moveCamera();
    
    this->stringWorld = std::make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }
}

void TextView::updateView(){
    this->outputView->setScene(this->textscene);
}

void TextView::protDead(int x, int y){
    changeSignAtCoord(x, y, 'D');
    this->textscene->clear();
    this->textscene->addText(*stringWorld,QFont("SF Mono"));
    
}

//code for poison flashing
void TextView::togglePoisoned(){
    if(toggle == 1){
        this->textscene->setBackgroundBrush(QColor("purple"));
        toggle = 0;
    } else{
        resetBg();
        toggle = 1;
    }
    timer.start();
}

//code for poison flashing
void TextView::healed(){
    this->textscene->setBackgroundBrush(QColor("green"));
    timer2.start();
}

void TextView::resetBg(){
    this->textscene->setBackgroundBrush(Qt::transparent);
}


void TextView::startTimer(){
    timer.start();
}

void TextView::stopTimer(){
    timer.stop();
    resetBg();
}

void TextView::moveCamera(){
    //cut world to size
    QString temp;
    qVecPlayer=qVec;
    auto before = ((world->getProtagonist()->getYPos()-4)*2)+1;
    
    //take world edges into account
    if(before <= 0){
        qVecPlayer=qVecPlayer.mid(before,17-before);
    }
    else qVecPlayer=qVecPlayer.mid(before,17);
    
    
    for (int i = 0; i < qVecPlayer.size(); i++) {
        //take world edges into account
        before = (world->getProtagonist()->getXPos()-7)*4;
        if(before <=0){
            temp = qVecPlayer[i].mid(before,60-before);
        }
        else {
            temp = qVecPlayer[i].mid(before,60);
        }
        temp.append("\n");
        qVecPlayer[i]=temp;
    }
    
}
