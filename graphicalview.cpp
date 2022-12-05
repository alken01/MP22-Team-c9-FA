#include "graphicalview.h"


graphicalview::graphicalview(std::shared_ptr<World> world)
{
    this->height = world->getRows();
    this->width = world->getCols();
    this->enemies = world->getEnemies();
    this->healthPacks = world->getHealthPacks();
    this->protagonist = world->getProtagonist();
}
