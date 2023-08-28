#include "viewcontroller.h"
#include <iostream>
ViewController::ViewController(std::shared_ptr<WorldModel> world)
    : graphicalView(std::make_shared<GraphicalView>()),
      textView(std::make_shared<TextView>()),
      _QTextView(std::make_shared<QGraphicsView>()),
      _QGraphicsView(std::make_shared<QGraphicsView>()),
      animationSpeed(500) {
    this->world = world;
    std::cout << "ViewController created" << std::endl;
}

void ViewController::drawWorlds() {
    std::cout << "viewcontroller drawWorlds" << std::endl;
    textView->draw(world, _QTextView);
    // graphicalView->draw(world, _QGraphicsView);
    std::cout << "drawWorlds done" << std::endl;
}

// mapchanger
void ::ViewController::changeMap() {
    std::cout << "viewcontroller changeMap" << std::endl;
    drawWorlds();
    updateViews();
}


void ViewController::fightEnemy(std::shared_ptr<Enemy> enemy) {
    float enemyValue = enemy->getValue();
    Tile::Type enemyType = enemy->getTileType();
    std::shared_ptr<Protagonist> protagonist = world->getProtagonist();
    fightingView();
    protagonist->decreaseHealth(enemyValue);

    if (enemyType == Tile::XEnemy) {
        float xEnemyEnergy =
        std::dynamic_pointer_cast<XEnemy>(enemy)->getEnergyLevel();
        protagonist->decreaseEnergy(xEnemyEnergy);
    } else if (enemyType == Tile::PEnemy) {
        protagonist->increasePoison(enemyValue);
        textView->setPoisoned();
    }

    // if (!isProtagonistAlive()) {
    //     dead();
    //     return;
    // }

    protagonist->setEnergy(MAX);
    std::dynamic_pointer_cast<Enemy>(enemy)->setDefeated(true);
    return;
}

void ViewController::updateViews() {
    // graphicalView->updateView();
    textView->moveProtagonist();
    textView->updateView();
}

void ViewController::dead() {
    textView->protagonistDies();
    textView->stopTimer();
}

void ViewController::fightingView() {
    textView->setFighting();
}

void ViewController::resetDelay() {
    delaySwitch = 0;
}


void ViewController::setAnimationSpeed(int newSpeed) {
    animationSpeed = newSpeed;
}

const std::shared_ptr<QGraphicsView>& ViewController::getQTextView() const {
    return _QTextView;
}
const std::shared_ptr<WorldModel>& ViewController::getWorld() const {
    return world;
}
const std::shared_ptr<QGraphicsView>& ViewController::getQGraphicsView() const {
    return _QGraphicsView;
}

void ViewController::setWorld(std::shared_ptr<WorldModel> world) {
    this->world = world;
}