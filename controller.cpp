#include "controller.h"

Controller::Controller(std::shared_ptr<WorldModel> w,std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t):
    graphical_view(g),text_view(t)
{
    this->world=w;
    this->graphical_view=g;
    this->text_view=t;
}


void Controller::handleInput() {

}

void Controller::update(){

}

void Controller::initWorlds(){
    this->text_view->draw(this->world, this->text_view);
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



void Controller::movePlayer(QString a){
    int x=world->getProtagonist()->getXPos();
    int y=world->getProtagonist()->getYPos();

    if(a=="up"){
        world->getProtagonist()->setYPos(y++);
        return;
    }

    if(a=="right"){
        world->getProtagonist()->setXPos(x++);
        return;
    }

    if(a=="left"){
        world->getProtagonist()->setXPos(x--);
        return;
    }

    if(a=="down"){
        world->getProtagonist()->setYPos(y--);
        return;
    }
}
