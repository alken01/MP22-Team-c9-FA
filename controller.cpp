#include "controller.h"

Controller::Controller(QMainWindow* mw,std::shared_ptr<World> w, std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t):
    world(w),graphical_view(g),text_view(t),window(mw)
{
    QGraphicsScene scene;
    this->width = w->getCols();
    this->height = w->getRows();
    this->qVec.clear();
    this->enemies = w->getEnemies();
    this->healthPacks = w->getHealthPacks();
    this->protagonist = w->getProtagonist();
    this->tiles = w->getTiles();
}


void Controller::handleInput() {

}

void Controller::update(){

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

QGraphicsScene* Controller::getScene() const
{
    return scene;
}

void Controller::movePlayer(QString a){
    int x=this->protagonist->getXPos();
    int y=this->protagonist->getYPos();

    if(a=="up"){
        this->protagonist->setYPos(y++);
        return;
    }

    if(a=="right"){
        this->protagonist->setXPos(x++);
        return;
    }

    if(a=="left"){
        this->protagonist->setXPos(x--);
        return;
    }

    if(a=="down"){
        this->protagonist->setYPos(y--);
        return;
    }
}
