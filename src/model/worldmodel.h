#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "world.h"
#include "xenemy.h"

class WorldModel {
    public:
        WorldModel(std::shared_ptr<World> w, int xEnemiesNumber);

        const std::vector<std::shared_ptr<Tile>>& getTiles() const;
        int getWidth() const;
        int getHeight() const;
        const std::vector<std::shared_ptr<Enemy>>& getEnemies() const;
        const std::vector<std::shared_ptr<Tile>>& getHealthPacks() const;
        const std::shared_ptr<Protagonist>& getProtagonist() const;
        const std::vector<std::vector<std::shared_ptr<Tile>>>& getWorldMap()
        const;
        float getTileValue(int x, int y);

    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        int width;
        int height;
        std::vector<std::shared_ptr<Enemy>> enemies;
        std::vector<std::shared_ptr<Tile>> healthPacks;
        std::shared_ptr<Protagonist> protagonist;
        std::vector<std::vector<std::shared_ptr<Tile>>> worldMap;

        void initMapVec();
};

#endif  // WORLDMODEL_H
