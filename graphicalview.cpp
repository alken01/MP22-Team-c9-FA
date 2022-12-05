#include "graphicalview.h"


graphicalview::graphicalview(std::shared_ptr<World> world)
{
    this->scene = world->
    this->enemies = world->getEnemies();
    this->healthPacks = world->getHealthPacks();

}
