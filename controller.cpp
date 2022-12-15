#include "controller.h"
#include <iostream>

Controller::Controller(std::shared_ptr<WorldModel> w,std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t):
    graphical_view(g),text_view(t)
{
    this->world=w;
    this->graphical_view=g;
    this->text_view=t;
    this->Qtext_view=std::make_shared<QGraphicsView>();
    this->Qgraphics_view=std::make_shared<QGraphicsView>();

    //command list - add new commands here
    commands.push_back("up");
    commands.push_back("down");
    commands.push_back("left");
    commands.push_back("right");
    commands.push_back("goto x y");
    commands.push_back("help");



    //also create QStringlist for use in autofill and switch
    for(unsigned long i =0; i<commands.size(); i++){
        completerList.append(commands.at(i));
    }
}



void Controller::handleInput() {

}

void Controller::update(){

}

void Controller::initWorlds(){
    this->world->getProtagonist()->setXPos(5);
    this->world->getProtagonist()->setYPos(5);
    this->text_view->draw(this->world, this->Qtext_view);
    this->graphical_view->draw(this->world, this->Qgraphics_view);
}

const std::shared_ptr<QGraphicsView> &Controller::getQgraphics_view() const
{
    return Qgraphics_view;
}

void Controller::setQgraphics_view(const std::shared_ptr<QGraphicsView> &newQgraphics_view)
{
    Qgraphics_view = newQgraphics_view;
}

const std::shared_ptr<WorldModel>& Controller::getWorld() const{
    return world;
}

void Controller::setWorld(const std::shared_ptr<WorldModel>& newWorld){
    world = newWorld;
}

const std::shared_ptr<QGraphicsView>& Controller::getQtext_view() const{
    return Qtext_view;
}

void Controller::setQtext_view(const std::shared_ptr<QGraphicsView>& newQtext_view){
    Qtext_view = newQtext_view;
}

const std::shared_ptr<TextView>& Controller::getText_view() const{
    return text_view;
}

void Controller::setText_view(const std::shared_ptr<TextView>& newText_view){
    text_view = newText_view;
}

//checks input from text and gets matching unique command
QString Controller::commandReceived(QString input){
    int count=0;
    std::vector<QString> resultSet;

    for(unsigned long i = 0; i < commands.size(); ++i){
        for(int j = 0; j < input.size(); ++j){
            if(j<commands[i].size()){
                if(input.at(j)==commands[i].at(j)){
                count++;
                }
            }
        }
        if(count==input.size()){
            resultSet.push_back(commands[i]);
        }
        count=0;
    }
    if(resultSet.size()==1){
        QString result = resultSet[0];
        std::cout << result.toStdString() << std::endl;
        movePlayer(result);
        return result;
    }
    else return NULL;
}

void Controller::movePlayer(QString input){

    if(alive == 1){
        //store old coordinate
        int x = world->getProtagonist()->getXPos();
        int y = world->getProtagonist()->getYPos();

        //new coordinate
        int x2 = x;
        int y2 = y;

        //folows order of commands added
        switch(completerList.indexOf(input)){
                case 0: //up
                    y2--; break;
                case 1: //down
                    y2++; break;
                case 2: //left
                    x2--; break;
                case 3: //right
                    x2++; break;
                case 4: //goto x y
                     break;
                case 5: //help handled in window
                     return;

            default:
                std::cout << "This is not a legal move" << std::endl;
            }


        if(x2<0 || y2<0 || x2>=world->getWidth() || y2>=world->getHeight()){ return;}

        // 0 health,1 enemy, 2 poison enemy, 3 wall, 4 tile
        auto test = checkMove(x2, y2);

        if(test == 3){
            std::cout.flush();
            std::cout << "you can't walk through walls" << std::endl;
            return;
        }

        if(test == 2){
            std::cout.flush();
            std::cout << "encountered poison enemy" << std::endl;
        }

        if(test == 1){
            std::cout.flush();
            std::cout << "encountered enemy" << std::endl;
        }

        if(test == 0){
            std::cout.flush();
            std::cout << "got healt yay" << std::endl;
        }

        world->getProtagonist()->setXPos(x2);
        world->getProtagonist()->setYPos(y2);

        this->text_view->movProtagonist(x, y, world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos(),world);

        //check if alive
        if(world->getProtagonist()->getHealth() == 0){
            dead(x2, y2);
        }

        if(world->getProtagonist()->getEnergy() == 0){
            dead(x2, y2);
        }

        this->text_view->updateView();
    }
}

int Controller::checkMove(int x, int y){
    auto test = world.get()->getWorldMap().at(x).at(y);

    //beaten enemy or used healthpack = -1 nothing happens
    if(test->getValue()==-1){
        return 4; //
    }

    //WALL
    if(test->getValue() == INFINITY){
        return 3; //is wall
    }

    //POISONED
    if(poisoned > 0){
        poisoned--; //one tile less poisoned
        world->getProtagonist()->setHealth(world->getProtagonist()->getHealth() - 1);
    } else text_view->stopTimer(); //stop poison effect

    //TILE + beaten enemy or used healthpack = -1
    if(test->getValue()<=1 && test->getValue()>=0){
        world->getProtagonist()->setEnergy(world->getProtagonist()->getEnergy()-test->getValue());

        return 4; //is tilethis->textscene->addText(*stringWorld,QFont("Monospace"));
    }


    //HEALTHPACK
    for(unsigned long i = 0; i < world->getHealthPacks().size(); ++i){
        int x = world->getHealthPacks().at(i)->getXPos();
        int y = world->getHealthPacks().at(i)->getYPos();
        if(test->getXPos() == x && test->getYPos() == y){

            //adding health
            auto health = world->getProtagonist()->getHealth();

            std::cout.flush();
            std::cout << "health added " << test->getValue() << std::endl;

            if(health + test->getValue() >= 100){
                world->getProtagonist()->setHealth(100);
            }
            else world->getProtagonist()->setHealth(health+test->getValue());

            text_view->healed();

            test->setValue(-1); //used
            return 0; // is health
        }
    }

    //POISON ENEMY
    if(std::dynamic_pointer_cast<PEnemy>(test)){

        std::cout.flush();
        std::cout << "Poisoned for:" << test->getValue() << std::endl;

        poisoned += test->getValue();
        world->getProtagonist()->setEnergy(100);
        test->setValue(-1); //beaten

        //start poison textview animation
        text_view->startTimer();

        return 2; //is poison enemy
    }


    //NORMAL ENEMY
    if(std::dynamic_pointer_cast<Enemy>(test)){

        std::cout.flush();
        std::cout << "damage added " << test->getValue() << std::endl;

        //damage done
        world->getProtagonist()->setHealth(world->getProtagonist()->getHealth() - test->getValue());
        world->getProtagonist()->setEnergy(100);
        test->setValue(-1); //beaten
        return 1; //is normal enemy
    }
    return -2;
}

void Controller::dead(int x, int y){
    this->text_view->protDead(x, y);
    text_view->stopTimer();
    this->alive = 0;
}

const QStringList &Controller::getCompleterList() const
{
    return completerList;
}

void Controller::setCompleterList(const QStringList &newCompleterList)
{
    completerList = newCompleterList;
}

const std::vector<QString> &Controller::getCommands() const
{
    return commands;
}

void Controller::setCommands(const std::vector<QString> &newCommands)
{
    commands = newCommands;
}

int Controller::getPoisoned() const{
    return poisoned;
}

void Controller::setPoisoned(int newPoisoned){
    poisoned = newPoisoned;
}

int Controller::getAlive() const{
    return alive;
}

void Controller::setAlive(int newAlive){
    alive = newAlive;
}

