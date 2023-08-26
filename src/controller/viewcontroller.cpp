#include "viewcontroller.h"
#include <iostream>
ViewController::ViewController(std::shared_ptr<Controller> controller)
    : graphicalView(std::make_shared<GraphicalView>()),
      textView(std::make_shared<TextView>()),
      _QTextView(std::make_shared<QGraphicsView>()),
      _QGraphicsView(std::make_shared<QGraphicsView>()),
      animationSpeed(500) {
    this->controller = controller;
    this->world = controller->getWorld();

    std::cout << "ViewController created" << std::endl;
}

void ViewController::drawWorlds() {
    std::cout << "viewcontroller drawWorlds" << std::endl;
    textView->draw(world, _QTextView);
    graphicalView->draw(world, _QGraphicsView);
    std::cout << "drawWorlds done" << std::endl;
}

// mapchanger
void ::ViewController::changeMap(QString mapName) {
    QString init_worldmap = getMapPath(mapName);
    auto newMap = std::make_shared<World>();
    QPixmap file(init_worldmap);
    int height = file.height();
    newMap->createWorld(init_worldmap, height / 2, height / 2, P_RATIO);
    world = std::make_shared<WorldModel>(newMap, XENEMY_NR);
    textView->stopTimer();
    textView->draw(world, _QTextView);

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

// const std::vector<Map>& ViewController::getMapList() const {
//     return mapList;
// }

const QStringList ViewController::getMapList() const {
    return mapList;
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
