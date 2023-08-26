#include "controller.h"

Controller::Controller() {
    initializeWorld();
}

void Controller::initializeWorld() {
    QString init_worldmap = getMapPath(mapList[0]);
    auto newMap = std::make_shared<World>();
    newMap->createWorld(init_worldmap, Controller::ENEMY_NR,
                        Controller::HEALTHPACK_NR, Controller::P_RATIO);
    world = std::make_shared<WorldModel>(newMap, Controller::XENEMY_NR);
}

void Controller::initWorlds() {
    Coordinates startCoord(7, 7);
    world->getProtagonist()->setCoordinates(startCoord);

    if (checkMove(startCoord) == Tile::Wall) {
        std::cout << "Controller movePlayer: invalid tile" << std::endl;
        Coordinates newCoord = world->getClosestValidTile(startCoord);
        world->getProtagonist()->setCoordinates(newCoord);
    }
}

void Controller::commandReceived(QString input) {
    if (input.size() >= 4 && input.left(4) == "goto") {
        // gotoHelper(input);
    } else {
        movePlayer(input);
    }
}

// move protagonist
void Controller::movePlayer(QString input) {
    std::cout << "Controller movePlayer" << std::endl;
    if (!isProtagonistAlive()) return;
    Coordinates oldCoord = world->getProtagonist()->getCoordinates();

    // if current tile is an invalid tile, return it to the closest valid tile
    if (checkMove(oldCoord) == Tile::Wall) {
        std::cout << "Controller movePlayer: invalid tile" << std::endl;
        Coordinates newCoord = world->getClosestValidTile(oldCoord);
        world->getProtagonist()->setCoordinates(newCoord);
        return;
    }

    Coordinates direction = CommandsMap::getMoveDirection(input);
    Coordinates newCoord = Coordinates((oldCoord.getX() + direction.getX()),
                                       (oldCoord.getY() + direction.getY()));

    bool isValidCoordinate = newCoord.getX() >= 0 && newCoord.getY() >= 0 &&
                             newCoord.getX() < world->getWidth() &&
                             newCoord.getY() < world->getHeight();
    if (!isValidCoordinate) return;

    if (checkMove(newCoord) == Tile::Wall) return;
    world->getProtagonist()->setCoordinates(newCoord);
    // viewController->movePlayer(oldCoord, newCoord);
}

int Controller::checkMove(Coordinates coord) {
    std::shared_ptr<Tile> checkTile =
    world->getTiles().at(coord.getX() + coord.getY() * world->getWidth());

    Tile::Type tileType = checkTile->getTileType();
    float tileValue = checkTile->getValue();
    if (tileType == Tile::Wall) return Tile::Wall;

    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();

    if (protagonist->getPoison() > 0) {
        protagonist->decreasePoison(POISON_RESISTANCE_PER_TURN);
        protagonist->decreaseHealth(POISON_DAMAGE);
    }

    protagonist->decreaseEnergy(1 - tileValue);  //TODO MAKE HELPER

    // is there an enemy on the tile?
    if (world->getEnemies().find(coord) != world->getEnemies().end()) {
        auto enemy = world->getEnemies().find(coord)->second;
        if (enemy->getDefeated()) return Tile::DefeatedEnemy;
        fightEnemy(world->getEnemies().find(coord)->second);
        return Tile::Enemy;
    }

    // is there a healthpack on the tile?
    if (world->getHealthPacks().find(coord) != world->getHealthPacks().end()) {
        auto healthpack = world->getHealthPacks().find(coord)->second;
        if (healthpack->getValue() == -1) return Tile::ConsumedHealthpack;
        protagonist->increaseHealth(
        world->getHealthPacks().find(coord)->second->getValue());
        healthpack->setValue(-1);
        return Tile::Healthpack;
    }

    return tileType;
}

void Controller::fightEnemy(std::shared_ptr<Enemy> enemy) {
    float enemyValue = enemy->getValue();
    Tile::Type enemyType = enemy->getTileType();
    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    protagonist->decreaseHealth(enemyValue);

    if (enemyType == Tile::XEnemy) {
        float xEnemyEnergy =
        std::dynamic_pointer_cast<XEnemy>(enemy)->getEnergyLevel();
        protagonist->decreaseEnergy(xEnemyEnergy);
    } else if (enemyType == Tile::PEnemy) {
        protagonist->increasePoison(enemyValue);
    }

    if (!isProtagonistAlive()) {
        return;
    }

    protagonist->setEnergy(MAX);
    std::dynamic_pointer_cast<Enemy>(enemy)->setDefeated(true);
    return;
}

bool Controller::isProtagonistAlive() {
    return world->getProtagonist()->getHealth() > 0 &&
           world->getProtagonist()->getEnergy() > 0;
}

void Controller::resetDelay() {
    delaySwitch = 0;
}

const QStringList& Controller::getMapList() const {
    return mapList;
}
void Controller::setAnimationSpeed(int newSpeed) {
    animationSpeed = newSpeed;
}
const std::shared_ptr<WorldModel>& Controller::getWorld() const {
    return world;
}
WorldModel& Controller::getWorldModel() {
    return *world;
}
