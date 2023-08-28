#include "aicontroller.h"
#include <iostream>

AIController::AIController(std::shared_ptr<WorldModel> world) {
    this->world = world;
    whiteValue = 0.0;
    // move = 0;
    animationSpeed = 100;
    // loop = 1;
}

void AIController::gotoHelper(QString input) {
    QStringList strList = input.split(" ");

    QString strX = strList.last();  // gets the last substring
    bool ok;
    int x =
    strX.toInt(&ok);  // convert the QString to an int, store the result in x

    if (!ok) {
        if (strX == "hp" || strX == "healthpack") {
            goToHealthpack();
            return;
        } else if (strX == "enemy") {
            goToEnemy();
            return;
        }
        qDebug() << "Error converting string to int";
        return;
    }

    strList.removeLast();           // removes the last item from the list
    QString strY = strList.last();  // gets the second-to-last substring

    int y = strY.toInt(&ok);
    if (!ok) {
        qDebug() << "Error converting string to int";
        return;
    }
    // call the helper function
    getPath(x, y);
}

float AIController::pathCost(vector<pair<int, int>> path) {
    float sum = 0.0;
    for (const auto& elem : path) {
        Coordinates coord(elem.first, elem.second);
        sum += world->getTileValue(coord);
    }
    return sum;
}

int AIController::goToHealthpack() {
    move = 0;
    Tile start(world->getProtagonist()->getXPos(),
               world->getProtagonist()->getYPos(), 0.0);
    vector<pair<int, int>> health_pack = {};
    float min_cost = -1;
    // find the path with the smallest length
    for (unsigned long i = 0; i < world->getHealthPacks().size(); ++i) {
        if (world->getHealthPackAtIndex(i) == nullptr) continue;
        Coordinates coord = world->getHealthPackAtIndex(i)->getCoordinates();
        Tile end(coord.getX(), coord.getY(), 0.0);
        vector<pair<int, int>> path = astar(world, start, end, whiteValue);
        float new_cost = pathCost(path);
        if (new_cost >= world->getProtagonist()->getEnergy()) continue;
        if (new_cost < min_cost || min_cost == -1) {
            health_pack = path;
            min_cost = new_cost;
        }
    }

    if (min_cost > -1) {
        goToPath(health_pack);
        return min_cost;
    }
    return -1;
}

int AIController::goToEnemy() {
    move = 0;
    Tile start(world->getProtagonist()->getXPos(),
               world->getProtagonist()->getYPos(), 0.0);
    vector<pair<int, int>> enemy_path = {};
    // max int value, yeah not the most elegant :(
    float min_cost = -1;
    // find the path with the smallest length
    for (unsigned long i = 0; i < world->getEnemies().size(); ++i) {
        if (world->getEnemyAtIndex(i)->getValue() == -1) continue;

        cout << world->getEnemyAtIndex(i)->getValue() << endl;

        int x = world->getEnemyAtIndex(i)->getXPos();
        int y = world->getEnemyAtIndex(i)->getYPos();
        Tile end(x, y, 0.0);
        vector<pair<int, int>> path = astar(world, start, end, whiteValue);
        float new_cost = pathCost(path);
        if (new_cost >= world->getProtagonist()->getEnergy()) continue;
        if (new_cost < min_cost || min_cost == -1) {
            enemy_path = path;
            min_cost = new_cost;
        }
    }

    if (min_cost > 0) {
        goToPath(enemy_path);
        return min_cost;
    }
    return -1;
}

void AIController::getPath(int x, int y) {
    move = 0;
    Coordinates coord = world->getProtagonist()->getCoordinates();
    Tile start(coord.getX(), coord.getY(), 0.0);
    Tile end(x, y, 0.0);
    vector<pair<int, int>> path = astar(world, start, end, whiteValue);
    goToPath(path);
}

void AIController::goToPath(vector<pair<int, int>> path) {
    if (path.empty()) return;
    vector<QString> textPath = pathToText(path);

    QTimer::singleShot(animationSpeed,
                       [this, textPath]() { makePathMoves(textPath); });
}

void AIController::makePathMoves(vector<QString> textPath) {
    if (move < textPath.size()) {
        // commandReceived(textPath.at(move));
        std::cout << textPath.at(move).toStdString() << std::endl;
        move++;
        QTimer::singleShot(animationSpeed,
                           [this, textPath]() { makePathMoves(textPath); });
    }
}

vector<QString> AIController::pathToText(vector<pair<int, int>> path) {
    // Resulting vector of directions
    vector<QString> directions;

    // Loop through the path and convert each pair of coordinates into a
    // direction
    for (size_t i = 1; i < path.size(); i++) {
        // Get the current and previous coordinates
        auto current = path[i];
        auto prev = path[i - 1];

        // Compare the coordinates and add the corresponding direction to the
        // result vector
        if (current.first > prev.first) {
            directions.push_back(QString("right"));
        } else if (current.first < prev.first) {
            directions.push_back(QString("left"));
        } else if (current.second > prev.second) {
            directions.push_back(QString("down"));
        } else if (current.second < prev.second) {
            directions.push_back(QString("up"));
        }
    }

    // Return the vector of directions
    return vector<QString>();
}

void AIController::autoPlay() {
    // if (!isProtagonistAlive() && loop) {
    //     QTimer::singleShot(animationSpeed * 2, [this]() { autoPlayLoop(); });
    // } else
    //     loop = 1;
    return;
}

void AIController::autoPlayLoop() {
    // if (loop) {
    //     if (goToEnemy() != -1) autoPlay();
    //     if (goToHealthpack() == -1) loop = 0;
    //     autoPlay();
    // }
}