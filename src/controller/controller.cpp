#include "controller.h"

Controller::Controller(std::shared_ptr<WorldModel> world) : world(world) {
    std::cout << "Controller created" << std::endl;
}

void Controller::handleInput(QString input) {
    if (input.size() >= 4 && input.left(4) == "goto") {
        // gotoHelper(input);
    } else {
        handleMovement(CommandsMap::getMoveDirection(input));
    }
}

void Controller::handleMovement(const Coordinates& direction) {
    if (!world->isProtagonistAlive()) return;

    Coordinates oldCoord = world->getProtagonist()->getCoordinates();
    Coordinates newCoord(oldCoord.getX() + direction.getX(),
                         oldCoord.getY() + direction.getY());

    if (!world->isValidCoordinate(newCoord)) return;

    if (world->getTileType(newCoord) == Tile::Wall) {
        newCoord = world->getClosestValidTile(newCoord);
        return;
    }

    world->getProtagonist()->setCoordinates(newCoord);
    handleTileInteraction(newCoord);
}

void Controller::handleTileInteraction(const Coordinates& coord) {
    Tile::Type tileType = world->getTileType(coord);
    std::cout << "Tile type: " << tileType << std::endl;

    if (world->getProtagonist()->getPoison() > 0) {
        world->getProtagonist()->decreasePoison(POISON_RESISTANCE_PER_TURN);
        world->getProtagonist()->decreaseHealth(POISON_DAMAGE);
    }
    // MAYBE CONSTANTS?
    world->getProtagonist()->decreaseEnergy(TILE_MAX - world->getTileValue(coord));

    if (tileType == Tile::Enemy) {
        handleEnemyInteraction(world->getEnemyAt(coord));
    } else if (tileType == Tile::Healthpack) {
        handleHealthPackInteraction(world->getHealthPackAt(coord));
    }
}

void Controller::handleEnemyInteraction(std::shared_ptr<Enemy> enemy) {
    if (enemy->getDefeated()) return;
    std::cout << "Fighting enemy" << std::endl;
    float enemyValue = enemy->getValue();
    Tile::Type enemyType = enemy->getTileType();

    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    std::cout << "Protagonist health: " << protagonist->getHealth() << std::endl;
    protagonist->decreaseHealth(enemyValue);
    std::cout << "Protagonist health: " << protagonist->getHealth() << std::endl;
    if (enemyType == Tile::XEnemy) {
        float xEnemyEnergy =
        std::dynamic_pointer_cast<XEnemy>(enemy)->getEnergyLevel();
        protagonist->decreaseEnergy(xEnemyEnergy);
    } else if (enemyType == Tile::PEnemy) {
        protagonist->increasePoison(enemyValue);
    }
    
    if (!world->isProtagonistAlive()) return;
    protagonist->setEnergy(MAX_ENERGY);
    std::dynamic_pointer_cast<Enemy>(enemy)->setDefeated(true);
}

void Controller::handleHealthPackInteraction(std::shared_ptr<Tile> healthpack) {
    if (healthpack->getValue() == -1) return;

    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    protagonist->increaseHealth(healthpack->getValue());
    healthpack->setValue(-1);
    std::cout << "Healthpack used" << std::endl;
}

void Controller::setWorld(std::shared_ptr<WorldModel> world) {
    this->world = world;
}