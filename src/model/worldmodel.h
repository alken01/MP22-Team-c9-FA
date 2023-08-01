#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"
#include "xenemy.h"

class WorldModel {
    public:
        WorldModel(std::shared_ptr<World> w, int xEnemiesNumber);

        const std::vector<std::shared_ptr<Tile>>& getTiles() const;
        const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
        const std::vector<std::shared_ptr<Tile>>& getHealthPacks() const;
        const std::shared_ptr<Protagonist>& getProtagonist() const;
        const std::vector<std::vector<std::shared_ptr<Tile>>>& getWorldMap()
        const;
        float getTileValue(Tile::Coordinates coord);
        int getWidth() const;
        int getHeight() const;

    private:
        int width;
        int height;
        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<Tile>> healthPacks;
        std::shared_ptr<Protagonist> protagonist;
        std::vector<std::vector<std::shared_ptr<Tile>>> worldMap;

        void populateWorldMap();
        template <typename T>
        std::vector<std::shared_ptr<T>> convertToShared(
        std::vector<std::unique_ptr<T>>& uniqueVector);
};

#endif  // WORLDMODEL_H
