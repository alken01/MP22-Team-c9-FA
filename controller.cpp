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
    this->world->getProtagonist()->setXPos(1);
     this->world->getProtagonist()->setYPos(1);
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
    int x=world->getProtagonist()->getXPos();
    int y=world->getProtagonist()->getYPos();

    if(a==1){
        world->getProtagonist()->setYPos(y+1);
    }

    if(a==2){
        world->getProtagonist()->setXPos(x+1);
    }

    if(a==3){
        world->getProtagonist()->setXPos(x-1);
    }

    if(a==4){
        world->getProtagonist()->setYPos(y-1);
    }

    this->text_view->movProtagonist(x,y,world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos());
    this->text_view->updateView(this->Qtext_view);
}
