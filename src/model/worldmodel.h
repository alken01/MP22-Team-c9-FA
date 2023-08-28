#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QHash>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "coordinates.h"
#include "map.h"
#include "world.h"
#include "xenemy.h"

class WorldModel {
    public:
        WorldModel(Map map, unsigned int xEnemiesNumber);
        const std::vector<std::shared_ptr<Tile>>& getTiles() const;
        const std::unordered_map<Coordinates, std::shared_ptr<Enemy>>&
        getEnemies() const;
        const std::unordered_map<Coordinates, std::shared_ptr<Tile>>&
        getHealthPacks() const;
        const std::shared_ptr<Protagonist>& getProtagonist() const;
        std::shared_ptr<Enemy> getEnemyAtIndex(size_t index);
        std::shared_ptr<Tile> getHealthPackAtIndex(size_t index);
        float getTileValue(Coordinates coord);
        int getWidth() const;
        int getHeight() const;
        Coordinates getClosestValidTile(Coordinates coord);

        // need to move them over to cpp
        bool isProtagonistAlive() const{return (protagonist->getHealth() > 0 && protagonist->getEnergy() > 0);}
        bool isValidCoordinate(Coordinates coord) const;
        Tile::Type getTileType(Coordinates coord) const{return tiles[coord.getX() + coord.getY() * width]->getTileType();}
        std::shared_ptr<Enemy> getEnemyAt(Coordinates coord) const{return enemies.at(coord);}
        std::shared_ptr<Tile> getHealthPackAt(Coordinates coord) const{return healthPacks.at(coord);}

    private:
        int width;
        int height;
        std::vector<std::shared_ptr<Tile>> tiles;
        std::unordered_map<Coordinates, std::shared_ptr<Enemy>> enemies;
        std::unordered_map<Coordinates, std::shared_ptr<Tile>> healthPacks;
        std::shared_ptr<Protagonist> protagonist;
        template <typename T>
        std::vector<std::shared_ptr<T>> convertToSharedVector(
        std::vector<std::unique_ptr<T>>& uniqueVector);
        template <typename T>
        std::unordered_map<Coordinates, std::shared_ptr<T>>
        convertToSharedUnorderedMap(
        std::vector<std::unique_ptr<T>>& uniqueVector);
        void createXEnemeies(unsigned int xEnemiesNumber);

        unsigned int ENEMY_NR = 50;
        unsigned int HEALTHPACK_NR = 15;
        float P_RATIO = 0.25f;
        unsigned int XENEMY_NR = 15;
};

#endif  // WORLDMODEL_H
