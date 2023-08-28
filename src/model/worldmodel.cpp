#include "worldmodel.h"

// Constructors and Initialization
WorldModel::WorldModel(Map map, unsigned int xEnemiesNumber) {
    // create world given map
    auto world = std::make_shared<World>();
    world->createWorld(map.getPath(), ENEMY_NR, HEALTHPACK_NR);
    width = world->getCols();
    height = world->getRows();

    // Get vectors of unique pointers from World
    std::vector<std::unique_ptr<Enemy>> enemyUnique = world->getEnemies();
    std::vector<std::unique_ptr<Tile>> healthUnique = world->getHealthPacks();
    std::vector<std::unique_ptr<Tile>> tilesUnique = world->getTiles();
    std::unique_ptr<Protagonist> protagonistUnique = world->getProtagonist();

    // Convert unique pointers to shared pointers using the helper function
    enemies = convertToSharedUnorderedMap(enemyUnique);

    healthPacks = convertToSharedUnorderedMap(healthUnique);
    tiles = convertToSharedVector(tilesUnique);
    protagonist = std::move(protagonistUnique);

    // check protagonist starting point
    if (map.getStartX() != -1 && map.getStartY() != -1) {
        protagonist->setCoordinates(
        Coordinates(map.getStartX(), map.getStartY()));
    } else {
        protagonist->setCoordinates(
        getClosestValidTile(protagonist->getCoordinates()));
    }

    createXEnemeies(xEnemiesNumber);
}

template <typename T>
std::vector<std::shared_ptr<T>> WorldModel::convertToSharedVector(
std::vector<std::unique_ptr<T>>& uniqueVector) {
    std::vector<std::shared_ptr<T>> sharedVector;
    std::transform(uniqueVector.begin(), uniqueVector.end(),
                   std::back_inserter(sharedVector),
                   [](std::unique_ptr<T>& ptr) { return std::move(ptr); });
    return sharedVector;
}

template <typename T>
std::unordered_map<Coordinates, std::shared_ptr<T>>
WorldModel::convertToSharedUnorderedMap(
std::vector<std::unique_ptr<T>>& uniqueVector) {
    std::vector<std::shared_ptr<T>> sharedVector =
    convertToSharedVector(uniqueVector);
    std::unordered_map<Coordinates, std::shared_ptr<T>> sharedMap;
    for (auto elem : sharedVector) {
        Coordinates coord = elem->getCoordinates();
        sharedMap[coord] = elem;
    }

    return sharedMap;
}

void WorldModel::createXEnemeies(unsigned int xEnemiesNumber) {
    for (unsigned int i = 0; i < xEnemiesNumber; ++i) {
        Coordinates coord;
        do {
            coord = Coordinates(rand() % width, rand() % height);
        } while (!isValidCoordinate(coord));
        enemies[coord] = std::make_shared<XEnemy>(coord.getX(), coord.getY(),
                                                  getTileValue(coord));
    }
}

// Utility Methods
std::shared_ptr<Tile> WorldModel::getTileAt(Coordinates coord) const {
    return tiles[coord.getX() + coord.getY() * getWidth()];
}

float WorldModel::getTileValue(Coordinates coord) const {
    if (enemies.find(coord) != enemies.end()) {
        return enemies.at(coord)->getValue();
    } else if (healthPacks.find(coord) != healthPacks.end()) {
        return healthPacks.at(coord)->getValue();
    }
    return getTileAt(coord)->getValue();
}

Tile::Type WorldModel::getTileType(Coordinates coord) const {
    if (enemies.find(coord) != enemies.end()) {
        return enemies.at(coord)->getTileType();
    } else if (healthPacks.find(coord) != healthPacks.end()) {
        return healthPacks.at(coord)->getTileType();
    }
    return getTileAt(coord)->getTileType();
}

std::shared_ptr<Enemy> WorldModel::getEnemyAt(Coordinates coord) const {
    return enemies.at(coord);
}

std::shared_ptr<Tile> WorldModel::getHealthPackAt(Coordinates coord) const {
    return healthPacks.at(coord);
}

std::shared_ptr<Enemy> WorldModel::getEnemyAtIndex(size_t index) const {
    if (index >= enemies.size()) {
        return nullptr;
    }
    auto it = enemies.begin();
    std::advance(it, index);
    return it->second;
}

std::shared_ptr<Tile> WorldModel::getHealthPackAtIndex(size_t index) const {
    if (index >= healthPacks.size()) {
        return nullptr;
    }
    auto it = healthPacks.begin();
    std::advance(it, index);
    return it->second;
}

Coordinates WorldModel::getClosestValidTile(Coordinates coord) {
    for (int i = 0; i < this->getHeight(); ++i) {
        for (int j = 0; j < this->getWidth(); ++j) {
            Coordinates tempCoord(i, j);
            if (getTileType(tempCoord) == Tile::NormalTile) {
                return tempCoord;
            }
        }
    }
    return coord;
}

bool WorldModel::isValidCoordinate(Coordinates coord) const {
    return !(isOutOfBounds(coord) || getTileType(coord) == Tile::Wall);
}

bool WorldModel::isOutOfBounds(Coordinates coord) const {
    return (coord.getX() < 0 || coord.getX() >= width || coord.getY() < 0 ||
            coord.getY() >= height);
}

bool WorldModel::isProtagonistAlive() const {
    return protagonist->isAlive();
}

bool WorldModel::isGameWon() const {
    return false;
}

// Getters
int WorldModel::getWidth() const {
    return width;
}

int WorldModel::getHeight() const {
    return height;
}

const std::vector<std::shared_ptr<Tile>>& WorldModel::getTiles() const {
    return tiles;
}

const std::unordered_map<Coordinates, std::shared_ptr<Enemy>>&
WorldModel::getEnemies() const {
    return enemies;
}

const std::unordered_map<Coordinates, std::shared_ptr<Tile>>&
WorldModel::getHealthPacks() const {
    return healthPacks;
}

const std::shared_ptr<Protagonist>& WorldModel::getProtagonist() const {
    return protagonist;
}
