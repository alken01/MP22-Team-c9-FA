#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <memory>

#include "commandsmap.h"
#include "coordinates.h"
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include "xenemy.h"

class Controller {
public:
    Controller(std::shared_ptr<WorldModel> world);

    void handleInput(QString input);
    void setAnimationSpeed(int newSpeed);
    void setWorld(std::shared_ptr<WorldModel> world);

private:
    int checkMove(Coordinates coord);
    void handleMovement(const Coordinates &direction);
    void handleTileInteraction(const Coordinates &coord);
    void handleEnemyInteraction(std::shared_ptr<Enemy> enemy);
    void handleHealthPackInteraction(std::shared_ptr<Tile> healthpack);

    std::shared_ptr<WorldModel> world;
    QTimer delayTimer;

    int animationSpeed, delaySwitch;

    static const int POISON_DAMAGE = 5;
    static const int POISON_RESISTANCE_PER_TURN = 1;
    static const int MAX_ENERGY = 100;
    static const int TILE_MAX = 1; // set it between 1 and 0
};

#endif  // CONTROLLER_H
