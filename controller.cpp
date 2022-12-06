#include "controller.h"

Controller::Controller(std::shared_ptr<World> w, std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t):
    world(w),graphical_view(g),text_view(t)
{
    QGraphicsScene* scene = new QGraphicsScene();
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

void Controller::switchToGraphic()
{
    // Make view 1 visible
    //graphical_view->draw(width,height,protagonist,enemies,healthPacks,scene,tiles);
    graphical_view->setVisible(true);
    text_view->setVisible(false);
}

void Controller::switchToText()
{
    // Make view 2 visible
    graphical_view->setVisible(false);
    text_view->setVisible(true);
}

QGraphicsScene* Controller::getScene() const
{
    return scene;
}
