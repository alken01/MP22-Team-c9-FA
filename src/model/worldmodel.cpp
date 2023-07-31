#include "worldmodel.h"

WorldModel::WorldModel(std::shared_ptr<World> w, int xEnemiesNumber)
    : width(w->getCols()),
      height(w->getRows()),
      protagonist(w->getProtagonist()) {
    auto enemyUnique = w->getEnemies();
    auto healthUnique = w->getHealthPacks();
    auto tilesUnique = w->getTiles();

     // Convert unique pointers to list of shared pointers using std::move
    std::move(enemyUnique.begin(), enemyUnique.end(), std::back_inserter(enemies));
    std::move(healthUnique.begin(), healthUnique.end(), std::back_inserter(healthPacks));
    std::move(tilesUnique.begin(), tilesUnique.end(), std::back_inserter(tiles));

    for (const auto& enemy : enemies) {
        unsigned long x = enemy->getXPos();
        unsigned long y = enemy->getYPos();

        // if normal enemy add x Xtype enemies
        if (xEnemiesNumber > 0) {
            enemies.push_back(
            std::make_shared<XEnemy>(x, y, enemy->getValue()));
            xEnemiesNumber--;
        }
    }

    initMapVec();
}

void WorldModel::initMapVec() {
    // init 2D array/check poison enemies
    std::vector<std::shared_ptr<Tile>> col(height, nullptr);
    worldMap = std::vector<std::vector<std::shared_ptr<Tile>>>(width, col);

    for (const auto& tile : tiles) {
        int x = tile->getXPos();
        int y = tile->getYPos();
        worldMap[x][y] = tile;
    }

    for (const auto& healthPack : healthPacks) {
        int x = healthPack->getXPos();
        int y = healthPack->getYPos();
        worldMap[x][y] = healthPack;
    }

    for (const auto& enemy : enemies) {
        int x = enemy->getXPos();
        int y = enemy->getYPos();
        worldMap[x][y] = enemy;
    }
}

// Getters
const std::vector<std::shared_ptr<Tile>>& WorldModel::getTiles() const {
    return tiles;
}

int WorldModel::getWidth() const {
    return width;
}

int WorldModel::getHeight() const {
    return height;
}

const std::vector<std::shared_ptr<Enemy>>& WorldModel::getEnemies() const {
    return enemies;
}

const std::vector<std::shared_ptr<Tile>>& WorldModel::getHealthPacks() const {
    return healthPacks;
}

const std::shared_ptr<Protagonist>& WorldModel::getProtagonist() const {
    return protagonist;
}

const std::vector<std::vector<std::shared_ptr<Tile>>>& WorldModel::getWorldMap()
const {
    return worldMap;
}

float WorldModel::getTileValue(int x, int y) {
    return getTiles()[x + y * getWidth()]->getValue();
}
