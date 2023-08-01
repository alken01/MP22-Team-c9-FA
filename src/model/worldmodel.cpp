#include "worldmodel.h"

WorldModel::WorldModel(std::shared_ptr<World> world, int xEnemiesNumber)
    : width(world->getCols()), height(world->getRows()) {
    //  print initialzing world
    std::cout << "Initializing world..." << std::endl;

    // Get vectors of unique pointers from World
    std::vector<std::unique_ptr<Enemy>> enemyUnique = world->getEnemies();
    std::vector<std::unique_ptr<Tile>> healthUnique = world->getHealthPacks();
    std::vector<std::unique_ptr<Tile>> tilesUnique = world->getTiles();
    std::unique_ptr<Protagonist> protagonistUnique = world->getProtagonist();

    // Convert unique pointers to shared pointers using the helper function
    enemies = convertToShared(enemyUnique);
    healthPacks = convertToShared(healthUnique);
    tiles = convertToShared(tilesUnique);
    protagonist = std::move(protagonistUnique);

    std::cout << "populateWorldMap" << std::endl;
    populateWorldMap();
}

template <typename T>
std::vector<std::shared_ptr<T>> WorldModel::convertToShared(
std::vector<std::unique_ptr<T>>& uniqueVector) {
    std::vector<std::shared_ptr<T>> sharedVector;
    std::transform(uniqueVector.begin(), uniqueVector.end(),
                   std::back_inserter(sharedVector),
                   [](std::unique_ptr<T>& ptr) { return std::move(ptr); });
    return sharedVector;
}

void WorldModel::populateWorldMap() {
    // init 2D array/check poison enemies
    std::vector<std::shared_ptr<Tile>> col(height, nullptr);
    worldMap = std::vector<std::vector<std::shared_ptr<Tile>>>(width, col);

    for (const std::shared_ptr<Tile>& tile : tiles) {
        const Tile::Coordinates& coords = tile->getCoordinates();
        worldMap[coords.xPos][coords.yPos] = tile;
    }

    for (const std::shared_ptr<Tile>& healthPack : healthPacks) {
        const Tile::Coordinates& coords = healthPack->getCoordinates();
        worldMap[coords.xPos][coords.yPos] = healthPack;
    }

    for (const std::shared_ptr<Enemy>& enemy : enemies) {
        const Tile::Coordinates& coords = enemy->getCoordinates();
        worldMap[coords.xPos][coords.yPos] = enemy;
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

float WorldModel::getTileValue(Tile::Coordinates coord) {
    return getTiles()[coord.xPos + coord.yPos * getWidth()]->getValue();
}
