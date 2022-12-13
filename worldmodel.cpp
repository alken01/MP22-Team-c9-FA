#include "worldmodel.h"
#include <iostream>

WorldModel::WorldModel(std::shared_ptr<World> w){
    this->width = w->getCols();
    this->height = w->getRows();
    auto enemyUnique = w->getEnemies();
    auto healthUnique = w->getHealthPacks();
    auto prot = w->getProtagonist();
    this->protagonist = std::move(prot);
    auto tilesUnique = w->getTiles();

    std::move(enemyUnique.begin(), enemyUnique.end(), std::back_inserter(this->enemies));
    std::move(healthUnique.begin(), healthUnique.end(), std::back_inserter(this->healthPacks));
    std::move(tilesUnique.begin(), tilesUnique.end(), std::back_inserter(this->tiles));


    //initialise 2D array of map tiles
    initMapVec();

    //tiles
    for(unsigned long i = 0; i < tiles.size(); ++i){
        int x = tiles.at(i)->getXPos();
        int y = tiles.at(i)->getYPos();
        worldMap.at(x).at(y) = tiles.at(i);
    }

    //health
    for(unsigned long i = 0; i < healthPacks.size(); ++i){
        int x = healthPacks.at(i)->getXPos();
        int y = healthPacks.at(i)->getYPos();
        worldMap.at(x).at(y) = healthPacks.at(i);
    }

    //enemies
    for(unsigned long i = 0; i < enemies.size(); ++i){
        int x = enemies.at(i)->getXPos();
        int y = enemies.at(i)->getYPos();
        worldMap.at(x).at(y) = enemies.at(i);
    }

}

const std::vector<std::shared_ptr<Tile> >& WorldModel::getTiles() const{
    return tiles;
}

void WorldModel::setTiles(const std::vector<std::shared_ptr<Tile> >& newTiles){
    tiles = newTiles;
}

int WorldModel::getWidth() const{
    return width;
}

void WorldModel::setWidth(int newWidth){
    width = newWidth;
}

int WorldModel::getHeight() const{
    return height;
}

void WorldModel::setHeight(int newHeight){
    height = newHeight;
}

const std::vector<std::shared_ptr<Enemy> >& WorldModel::getEnemies() const{
    return enemies;
}

void WorldModel::setEnemies(const std::vector<std::shared_ptr<Enemy> >& newEnemies){
    enemies = newEnemies;
}

const std::vector<std::shared_ptr<Tile> >& WorldModel::getHealthPacks() const{
    return healthPacks;
}

void WorldModel::setHealthPacks(const std::vector<std::shared_ptr<Tile> >& newHealthPacks){
    healthPacks = newHealthPacks;
}

const std::shared_ptr<Protagonist>& WorldModel::getProtagonist() const{
    return protagonist;
}

void WorldModel::setProtagonist(const std::shared_ptr<Protagonist>& newProtagonist){
    protagonist = newProtagonist;
}

const std::vector<std::vector<std::shared_ptr<Tile> > >& WorldModel::getWorldMap() const{
    return worldMap;
}

void WorldModel::setWorldMap(const std::vector<std::vector<std::shared_ptr<Tile> > >& newWorldMap){
    worldMap = newWorldMap;
}

void WorldModel::initMapVec(){
    //init 2D array/check poison enemies

    std::vector<std::shared_ptr<Tile>> col;
    for(int i = 0; i < this->height; i++){
        col.push_back(nullptr);
    }

    for(int i = 0; i < this->width; i++){
        worldMap.push_back(col);
    }
}
