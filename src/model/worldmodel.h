#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "coordinates.h"
#include "map.h"
#include "world.h"
#include "xenemy.h"

class WorldModel {
    public:
        WorldModel(Map map, unsigned int xEnemiesNumber);

        std::shared_ptr<Tile> getTileAt(Coordinates coord) const;
        float getTileValue(Coordinates coord) const;
        Tile::Type getTileType(Coordinates coord) const;

        std::shared_ptr<Enemy> getEnemyAt(Coordinates coord) const;
        std::shared_ptr<Tile> getHealthPackAt(Coordinates coord) const;

        std::shared_ptr<Enemy> getEnemyAtIndex(size_t index) const;
        std::shared_ptr<Tile> getHealthPackAtIndex(size_t index) const;

        Coordinates getClosestValidTile(Coordinates coord);

        bool isValidCoordinate(Coordinates coord) const;
        bool isOutOfBounds(Coordinates coord) const;
        bool isProtagonistAlive() const;
        bool isGameWon() const;

        // Getters
        int getWidth() const;
        int getHeight() const;
        const std::vector<std::shared_ptr<Tile>>& getTiles() const;
        const std::unordered_map<Coordinates, std::shared_ptr<Enemy>>& getEnemies() const;
        const std::unordered_map<Coordinates, std::shared_ptr<Tile>>& getHealthPacks() const;
        const std::shared_ptr<Protagonist>& getProtagonist() const;

    private:
        unsigned int ENEMY_NR = 10;
        unsigned int HEALTHPACK_NR = 5;
        int width;
        int height;

        std::vector<std::shared_ptr<Tile>> tiles;
        std::unordered_map<Coordinates, std::shared_ptr<Enemy>> enemies;
        std::unordered_map<Coordinates, std::shared_ptr<Tile>> healthPacks;
        std::shared_ptr<Protagonist> protagonist;

        template <typename T>
        std::vector<std::shared_ptr<T>> convertToSharedVector(std::vector<std::unique_ptr<T>>& uniqueVector);

        template <typename T>
        std::unordered_map<Coordinates, std::shared_ptr<T>>
        convertToSharedUnorderedMap(std::vector<std::unique_ptr<T>>& uniqueVector);
        void createXEnemeies(unsigned int xEnemiesNumber);
};

#endif  // WORLDMODEL_H
