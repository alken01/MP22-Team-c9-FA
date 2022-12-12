#include "controller.h"
#include <iostream>

Controller::Controller(std::shared_ptr<WorldModel> w,std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t):
    graphical_view(g),text_view(t)
{
    this->world=w;
    this->graphical_view=g;
    this->text_view=t;
    this->Qtext_view=std::make_shared<QGraphicsView>();
}


void Controller::handleInput() {

}

void Controller::update(){

}

void Controller::initWorlds(){
    this->world->getProtagonist()->setXPos(4);
     this->world->getProtagonist()->setYPos(4);
    this->text_view->draw(this->world, this->Qtext_view);
}

const std::shared_ptr<WorldModel> &Controller::getWorld() const
{
    return world;
}

void Controller::setWorld(const std::shared_ptr<WorldModel> &newWorld)
{
    world = newWorld;
}

const std::shared_ptr<QGraphicsView> &Controller::getQtext_view() const
{
    return Qtext_view;
}

void Controller::setQtext_view(const std::shared_ptr<QGraphicsView> &newQtext_view)
{
    Qtext_view = newQtext_view;
}

const std::shared_ptr<TextView> &Controller::getText_view() const
{
    return text_view;
}

void Controller::setText_view(const std::shared_ptr<TextView> &newText_view)
{
    text_view = newText_view;
}

void Controller::switchViews()
{
    if (graphical_view->isVisible())
        {
            graphical_view->hide();
            text_view->show();
        }
        else
        {
            graphical_view->hide();
            text_view->show();
        }
}



void Controller::movePlayer(int a){
    //store old coordinate
    int x=world->getProtagonist()->getXPos();
    int y=world->getProtagonist()->getYPos();

    //new coordinate
    int x2=x;
    int y2=y;

    if(a==1){ //up
        y2++;
    }

    if(a==2){ //right
        x2++;
    }

    if(a==3){ //left
        x2--;
    }

    if(a==4){ //down
       y2--;
    }

    // 0 health,1 enemy, 2 poison enemy, 3 wall, 4 tile
    auto test=checkMove(x2, y2);

    if(test==3){
        std::cout.flush();
        std::cout << "you can't walk through walls" << std::endl;
        return;
    }

    if(test==2){
        std::cout.flush();
        std::cout << "encountered poison enemy" << std::endl;
    }

    if(test==1){
        std::cout.flush();
        std::cout << "encountered enemy" << std::endl;
    }

    if(test==0){
        std::cout.flush();
        std::cout << "got healt yay" << std::endl;
    }

    if(test==-1){
        std::cout.flush();
        std::cout << "error occured: tile not found" << std::endl;
    }

    world->getProtagonist()->setXPos(x2);
    world->getProtagonist()->setYPos(y2);

    this->text_view->movProtagonist(x,y,world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos());
    this->text_view->updateView(this->Qtext_view);
}

int Controller::checkMove(int x, int y){
    auto test = world.get()->getWorldMap().at(x).at(y);

    if(test->getValue()==1){
        return 4; //is tile
    }

    if(test->getValue()==INFINITY){
        return 3; //is wall
    }

    for (unsigned long i = 0; i < world->getHealthPacks().size(); ++i) {
        int x =world->getHealthPacks().at(i)->getXPos();
        int y =world->getHealthPacks().at(i)->getYPos();
        if(test->getXPos()==x && test->getYPos()==y){
            return 0; // is health
        }
    }

    if(std::dynamic_pointer_cast<PEnemy>(test)){
        return 2; //is poison enemy
      }


    if(std::dynamic_pointer_cast<Enemy>(test)){
        return 1; //is normal enemy
    }
    return -1;
}
