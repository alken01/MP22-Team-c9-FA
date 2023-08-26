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
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include "xenemy.h"
#include "coordinates.h"

class Controller {
    public:
        Controller();

        void handleInput();
        bool isProtagonistAlive();
        void commandReceived(QString input);
        void movePlayer(QString input);
        void fightEnemy(std::shared_ptr<Enemy> enemy);

        const QStringList& getMapList() const;
        void setAnimationSpeed(int newSpeed);
        const std::shared_ptr<WorldModel>& getWorld() const;
        WorldModel& getWorldModel();

    private:
        void initializeWorld();
        void initWorlds();
        int checkMove(Coordinates coord);
        void resetDelay();
        
        // CHANGE THIS
        QStringList mapList = {"maze1", "maze2", "maze3", "worldmap",
                               "worldmap4"};
        QString mapPath = ":/resources/world_images/";
        QString getMapPath(QString mapName) {
            return mapPath + mapName + ".png";
        }

        std::shared_ptr<WorldModel> world;
        QTimer delayTimer;

        int animationSpeed, delaySwitch;
        std::size_t move, loop;

        const unsigned int ENEMY_NR = 50;
        const unsigned int HEALTHPACK_NR = 5;
        const float P_RATIO = 0.25f;
        const unsigned int XENEMY_NR = 3;

        int POISON_DAMAGE = 5;
        int POISON_RESISTANCE_PER_TURN = 1;
        int MAX = 100;
};

#endif  // CONTROLLER_H