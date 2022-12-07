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
//    int x=this->protagonist->getXPos();
//    int y=this->protagonist->getYPos();

//    if(a=="up"){
//        this->protagonist->setYPos(y++);
//        return;
//    }

//    if(a=="right"){
//        this->protagonist->setXPos(x++);
//        return;
//    }

//    if(a=="left"){
//        this->protagonist->setXPos(x--);
//        return;
//    }

//    if(a=="down"){
//        this->protagonist->setYPos(y--);
//        return;
//    }
}
