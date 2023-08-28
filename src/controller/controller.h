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

        int handleInput(QString input);
        void setWorld(std::shared_ptr<WorldModel> world);

        static const int MOVE = 0;
        static const int FIGHT = 1;
        static const int XFIGHT = 2;
        static const int POISON = 3;
        static const int HEAL = 4;
        static const int DIE = -1;


    private:
        int handleMovement(const Coordinates& direction);
        int handleTileInteraction(const Coordinates& coord);
        int handleEnemyInteraction(std::shared_ptr<Enemy> enemy);
        int handleHealthPackInteraction(std::shared_ptr<Tile> healthpack);

        std::shared_ptr<WorldModel> world;
        QTimer delayTimer;

        static const int POISON_DAMAGE = 5;
        static const int POISON_RESISTANCE_PER_TURN = 1;
        static const int MAX_ENERGY = 100;
        static const int TILE_MAX = 1;  // set it between 1 and 0
};

#endif  // CONTROLLER_H
