#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QHash>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"
#include "xenemy.h"
#include "coordinates.h"

class WorldModel {
    public:
        WorldModel(std::shared_ptr<World> world, unsigned int xEnemiesNumber);
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

    private:
        int width;
        int height;
        std::vector<std::shared_ptr<Tile>> tiles;
        std::unordered_map<Coordinates, std::shared_ptr<Enemy>> enemies;
        std::unordered_map<Coordinates, std::shared_ptr<Tile>>
        healthPacks;
        std::shared_ptr<Protagonist> protagonist;
        template <typename T>
        std::vector<std::shared_ptr<T>> convertToSharedVector(
        std::vector<std::unique_ptr<T>>& uniqueVector);
        template <typename T>
        std::unordered_map<Coordinates, std::shared_ptr<T>>
        convertToSharedUnorderedMap(
        std::vector<std::unique_ptr<T>>& uniqueVector);
        void createXEnemeies(unsigned int xEnemiesNumber);
};

#endif  // WORLDMODEL_H
