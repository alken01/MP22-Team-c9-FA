#include "worldmodel.h"
#include "xenemy.h"
#include <iostream>
using namespace std;

WorldModel::WorldModel(shared_ptr<World> w, int xEnemies){
    width = w->getCols();
    height = w->getRows();
    auto enemyUnique = w->getEnemies();
    auto healthUnique = w->getHealthPacks();
    auto prot = w->getProtagonist();
    protagonist = move(prot);
    auto tilesUnique = w->getTiles();

    //convert unique pointers to list of shared ptrs
    move(enemyUnique.begin(), enemyUnique.end(), back_inserter(enemies));
    move(healthUnique.begin(), healthUnique.end(), back_inserter(healthPacks));
    move(tilesUnique.begin(), tilesUnique.end(), back_inserter(tiles));

    //add X enemies
    for (unsigned long i = 0; i <enemies.size(); ++i) {
        unsigned long x = enemies.at(i)->getXPos();
        unsigned long y = enemies.at(i)->getYPos();

        //if normal enemy add x Xtype enemies
        if(!dynamic_pointer_cast<PEnemy>(enemies.at(i)) && xEnemies>0){
                auto xEnemy = make_shared<XEnemy>(x,y,enemies.at(i)->getValue());
                enemies.at(i)=xEnemy;
                xEnemies--;
            }
    }


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

void WorldModel::initMapVec(){
    //init 2D array/check poison enemies

    vector<shared_ptr<Tile>> col;
    for(int i = 0; i < height; i++){
        col.push_back(nullptr);
    }

    for(int i = 0; i < width; i++){
        worldMap.push_back(col);
    }
}

//Getters and Setters
const vector<shared_ptr<Tile> >& WorldModel::getTiles() const{
    return tiles;
}

void WorldModel::setTiles(const vector<shared_ptr<Tile> >& newTiles){
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

const vector<shared_ptr<Enemy> >& WorldModel::getEnemies() const{
    return enemies;
}

void WorldModel::setEnemies(const vector<shared_ptr<Enemy> >& newEnemies){
    enemies = newEnemies;
}

const vector<shared_ptr<Tile> >& WorldModel::getHealthPacks() const{
    return healthPacks;
}

void WorldModel::setHealthPacks(const vector<shared_ptr<Tile> >& newHealthPacks){
    healthPacks = newHealthPacks;
}

const shared_ptr<Protagonist>& WorldModel::getProtagonist() const{
    return protagonist;
}

void WorldModel::setProtagonist(const shared_ptr<Protagonist>& newProtagonist){
    protagonist = newProtagonist;
}

const vector<vector<shared_ptr<Tile> > >& WorldModel::getWorldMap() const{
    return worldMap;
}

float WorldModel::getTileValue(int x, int y){
    return getTiles()[x+y*getWidth()]->getValue();
}
void WorldModel::setWorldMap(const vector<vector<shared_ptr<Tile> > >& newWorldMap){
    worldMap = newWorldMap;
}

