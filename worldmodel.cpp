#include "worldmodel.h"

WorldModel::WorldModel(std::shared_ptr<World> w)
{
    this->width = w->getCols();
    this->height = w->getRows();
    this->enemies = w->getEnemies();
    this->healthPacks = w->getHealthPacks();
    this->protagonist = w->getProtagonist();
    this->tiles = w->getTiles();
}

const std::vector<std::shared_ptr<Tile> > &WorldModel::getTiles() const
{
    return tiles;
}

void WorldModel::setTiles(const std::vector<std::shared_ptr<Tile> > &newTiles)
{
    tiles = newTiles;
}

int WorldModel::getWidth() const
{
    return width;
}

void WorldModel::setWidth(int newWidth)
{
    width = newWidth;
}

int WorldModel::getHeight() const
{
    return height;
}

void WorldModel::setHeight(int newHeight)
{
    height = newHeight;
}

const std::vector<std::shared_ptr<Enemy> > &WorldModel::getEnemies() const
{
    return enemies;
}

void WorldModel::setEnemies(const std::vector<std::shared_ptr<Enemy> > &newEnemies)
{
    enemies = newEnemies;
}

const std::vector<std::shared_ptr<Tile> > &WorldModel::getHealthPacks() const
{
    return healthPacks;
}

void WorldModel::setHealthPacks(const std::vector<std::shared_ptr<Tile> > &newHealthPacks)
{
    healthPacks = newHealthPacks;
}

Tile*WorldModel::getProtagonist() const
{
    return protagonist.get();
}

void WorldModel::setProtagonist(std::shared_ptr<Tile> newProtagonist)
{
    protagonist = std::move(newProtagonist);
}

