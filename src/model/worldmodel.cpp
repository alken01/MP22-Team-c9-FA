#include "worldmodel.h"

WorldModel::WorldModel(Map map, unsigned int xEnemiesNumber) {
    // create world given map
    auto world = std::make_shared<World>();
    world->createWorld(map.getPath(), ENEMY_NR, HEALTHPACK_NR, P_RATIO);
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
    if(map.getStartX() != -1 && map.getStartY() != -1) {
        protagonist->setCoordinates(Coordinates(map.getStartX(), map.getStartY()));
    } else {
        protagonist->setCoordinates(getClosestValidTile(protagonist->getCoordinates()));
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
    // if (xEnemiesNumber > enemies.size()) {
    //     xEnemiesNumber = enemies.size();
    // }
    // for (unsigned int i = 0; i < xEnemiesNumber; i++) {
    //     // get the position of the first enemies
    //     int xPos = enemies[i]->getCoordinates().xPos;
    //     int yPos = enemies[i]->getCoordinates().yPos;
    //     float strength = enemies[i]->getValue();
    //     // remove the enemy
    //     enemies.erase(enemies.begin() + i);
    //     // add the XEnemy
    //     enemies.push_back(std::make_shared<XEnemy>(xPos, yPos, strength));
    // }
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

float WorldModel::getTileValue(Coordinates coord) {
    return getTiles()[coord.getX() + coord.getY() * getWidth()]->getValue();
}

std::shared_ptr<Enemy> WorldModel::getEnemyAtIndex(size_t index) {
    if (index >= enemies.size()) {
        return nullptr;
    }

    auto it = enemies.begin();
    std::advance(it, index);
    return it->second;
}

std::shared_ptr<Tile> WorldModel::getHealthPackAtIndex(size_t index) {
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
            auto tile = this->getTiles()[i * this->getWidth() + j];
            if (tile->getTileType() == Tile::NormalTile) {
                return tile->getCoordinates();
            }
        }
    }
    return coord;
}

bool WorldModel::isValidCoordinate(Coordinates coord) const {
    // check if the coordinate is within the map and it is not a tile
    // that is not walkable
    return (coord.getX() >= 0 && coord.getX() < width && coord.getY() >= 0 &&
            coord.getY() < height &&
            tiles[coord.getX() + coord.getY() * width]->getTileType() !=
            Tile::Wall);
}