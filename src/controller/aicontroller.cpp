#include "aicontroller.h"
#include <QTimer>
#include <iostream>

AIController::AIController(std::shared_ptr<WorldModel> world){
    this->world = world;
    whiteValue = 1.0;
    animationSpeed = 100;
    move = 0;
    astar = std::make_shared<AStar>(world);
    std::cout << "world width" << world->getWidth() << std::endl;
}

std::vector<QString> AIController::gotoHelper(QString input) {
    QStringList strList = input.split(" ");
    if (strList.isEmpty()) return std::vector<QString>();

    QString strX = strList.last();
    bool ok;
    int x = strX.toInt(&ok);

    if (!ok) {
        if (strX == "hp" || strX == "healthpack") {
            goToHealthpack();
        } else if (strX == "enemy") {
            goToEnemy();
        } else {
        }
    } else {
        strList.removeLast();
        QString strY = strList.last();
        int y = strY.toInt(&ok);
        if (ok) {
            return getPath(x, y);
        }
    }
    return std::vector<QString>();
}

std::vector<QString> AIController::getPath(int x, int y) {
    move = 0;
    Coordinates start = world->getProtagonist()->getCoordinates();
    Coordinates end(x, y);
    std::cout << "start: " << start.getX() << ", " << start.getY() << std::endl;
    std::vector<Coordinates> path = astar->findPath(start, end, whiteValue);
    return pathToText(path);
}

float AIController::pathCost(const std::vector<std::pair<int, int>>& path) {
//     float sum = 0.0;
//     for (const auto& elem : path) {
//         Coordinates coord(elem.first, elem.second);
//         sum += world->getTileValue(coord);
//     }
//     return sum;
return 0;
}

int AIController::goToHealthpack() {
//     move = 0;
//     Tile start(world->getProtagonist()->getXPos(),
//                world->getProtagonist()->getYPos(), 0.0);
//     vector<pair<int, int>> health_pack;
//     float min_cost = -1;

//     for (unsigned long i = 0; i < world->getHealthPacks().size(); ++i) {
//         if (world->getHealthPackAtIndex(i) == nullptr) continue;
//         Coordinates coord = world->getHealthPackAtIndex(i)->getCoordinates();
//         Tile end(coord.getX(), coord.getY(), 0.0);
//         vector<pair<int, int>> path = astar(world, start, end, whiteValue);
//         float new_cost = pathCost(path);
//         if (new_cost < world->getProtagonist()->getEnergy() &&
//             (new_cost < min_cost || min_cost == -1)) {
//             health_pack = path;
//             min_cost = new_cost;
//         }
//     }

//     if (min_cost > -1) {
//         goToPath(health_pack);
//         return min_cost;
//     }
    return -1;
}

int AIController::goToEnemy() {
//     move = 0;
//     Tile start(world->getProtagonist()->getXPos(),
//                world->getProtagonist()->getYPos(), 0.0);
//     vector<pair<int, int>> enemy_path;
//     float min_cost = -1;

//     for (unsigned long i = 0; i < world->getEnemies().size(); ++i) {
//         if (world->getEnemyAtIndex(i)->getValue() == -1) continue;
//         int x = world->getEnemyAtIndex(i)->getXPos();
//         int y = world->getEnemyAtIndex(i)->getYPos();
//         Tile end(x, y, 0.0);
//         vector<pair<int, int>> path = astar(world, start, end, whiteValue);
//         float new_cost = pathCost(path);
//         if (new_cost < world->getProtagonist()->getEnergy() &&
//             (new_cost < min_cost || min_cost == -1)) {
//             enemy_path = path;
//             min_cost = new_cost;
//         }
//     }

//     if (min_cost > 0) {
//         goToPath(enemy_path);
//         return min_cost;
//     }
    return -1;
}



// void AIController::goToPath(const vector<pair<int, int>>& path) {
//     if (path.empty()) return;
//     vector<QString> textPath = pathToText(path);

//     QTimer::singleShot(animationSpeed,
//                        [this, textPath]() { makePathMoves(textPath); });
// }

// void AIController::makePathMoves(const vector<QString>& textPath) {
//     if (move < textPath.size()) {
//         std::cout << textPath.at(move).toStdString() << std::endl;
//         move++;
//         QTimer::singleShot(animationSpeed,
//                            [this, textPath]() { makePathMoves(textPath); });
//     }
// }

std::vector<QString> AIController::pathToText(const std::vector<Coordinates> path) {
    std::vector<QString> directions;

    for (size_t i = 1; i < path.size(); i++) {
        auto current = path[i];
        auto prev = path[i - 1];

        if (current.getX() > prev.getX()) {
            directions.push_back(QString("right"));
        } else if (current.getX() < prev.getX()) {
            directions.push_back(QString("left"));
        } else if (current.getY() > prev.getY()) {
            directions.push_back(QString("down"));
        } else if (current.getY() < prev.getY()) {
            directions.push_back(QString("up"));
        }
    }

    return directions;
}

void AIController::autoPlay() {
//     // if (!isProtagonistAlive() && loop) {
//     //     QTimer::singleShot(animationSpeed * 2, [this]() { autoPlayLoop(); });
//     // } else
//     //     loop = 1;

}

// void AIController::autoPlayLoop() {
//     // if (loop) {
//     //     if (goToEnemy() != -1) autoPlay();
//     //     if (goToHealthpack() == -1) loop = 0;
//     //     autoPlay();
//     // }
// }

void AIController::setWhiteValue(float whiteValue) {
    this->whiteValue = whiteValue;
}

void AIController::setAnimationSpeed(int animationSpeed) {
    this->animationSpeed = animationSpeed;
}

// getAnimation
int AIController::getAnimation() {
    return animationSpeed;
}
void AIController::setWorld(std::shared_ptr<WorldModel> world) {
    this->world = world;
    // create a new astar object with the new world
    astar = std::make_shared<AStar>(world);

}