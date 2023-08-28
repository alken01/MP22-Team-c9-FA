#include "controller.h"

Controller::Controller(std::shared_ptr<WorldModel> world) : world(world) {}

int Controller::handleInput(QString input) {
    if (input.size() >= 4 && input.left(4) == "goto") {
        // gotoHelper(input);
    }
    return handleMovement(CommandsMap::getMoveDirection(input));
}

int Controller::handleMovement(const Coordinates& direction) {
    if (!world->isProtagonistAlive()) return DIE;

    Coordinates oldCoord = world->getProtagonist()->getCoordinates();
    Coordinates newCoord(oldCoord.getX() + direction.getX(),
                         oldCoord.getY() + direction.getY());

    if (!world->isValidCoordinate(newCoord)) return MOVE;

    world->getProtagonist()->setCoordinates(newCoord);
    return handleTileInteraction(newCoord);
}

int Controller::handleTileInteraction(const Coordinates& coord) {
    Tile::Type tileType = world->getTileType(coord);

    if (world->getProtagonist()->getPoison() > 0) {
        world->getProtagonist()->decreasePoison(POISON_RESISTANCE_PER_TURN);
        world->getProtagonist()->decreaseHealth(POISON_DAMAGE);
    }

    world->getProtagonist()->decreaseEnergy(TILE_MAX - world->getTileValue(coord)); 

    if (tileType == Tile::Enemy || tileType == Tile::XEnemy || tileType == Tile::PEnemy) {
        return handleEnemyInteraction(world->getEnemyAt(coord));
    } else if (tileType == Tile::Healthpack) {
        return handleHealthPackInteraction(world->getHealthPackAt(coord));
    }
}

int Controller::handleEnemyInteraction(std::shared_ptr<Enemy> enemy) {
    if (enemy->getDefeated()) return MOVE;
    int result = FIGHT;
    float enemyValue = enemy->getValue();
    Tile::Type enemyType = enemy->getTileType();

    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    protagonist->decreaseHealth(enemyValue);
    if (enemyType == Tile::XEnemy) {
        float xEnemyEnergy =
        std::dynamic_pointer_cast<XEnemy>(enemy)->getEnergyLevel();
        protagonist->decreaseEnergy(xEnemyEnergy);
        result = XFIGHT;
    } else if (enemyType == Tile::PEnemy) {
        protagonist->increasePoison(enemyValue);
        result = POISON;
    }

    if (!world->isProtagonistAlive()) return DIE;

    protagonist->setEnergy(MAX_ENERGY);
    std::dynamic_pointer_cast<Enemy>(enemy)->setDefeated(true);
    return result;
}

int Controller::handleHealthPackInteraction(std::shared_ptr<Tile> healthpack) {
    if (healthpack->getValue() == -1) return MOVE;
    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    protagonist->increaseHealth(healthpack->getValue());
    healthpack->setValue(-1);
    return HEAL;
}

void Controller::setWorld(std::shared_ptr<WorldModel> world) {
    this->world = world;
}