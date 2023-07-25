#pragma once

#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <memory>
#include "astar.h"
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include "xenemy.h"

class GameController : public QObject
{
        Q_OBJECT
    public:
        GameController();

        bool isAlive() const { return alive; }
        void setAlive(bool status) { alive = status; }
        const QStringList& getCommands() const { return commands; }
        const QStringList& getMapList() const { return mapList; }
        const QString& getTerminalOut() const { return terminalOut; }
        void setTerminalOut(const QString& newOut) { terminalOut = newOut; }
        bool getWin() const { return win; }
        void setAnimationSpeed(int newSpeed) { animationSpeed = newSpeed; }

        void initWorlds();
        void restart();

    public slots:
        void handleInput(QString input);
        void changeMap(QString mapName);
        void movePlayer(QString input);
        void switchToGraphic();
        void switchToText();
        void switchViews();

    private:
        QStringList commands = {"up",       "down",       "left",    "right",
                                "goto x y", "goto enemy", "goto hp", "help"};
        QStringList mapList = {"maze1", "maze2", "maze3", "worldmap",
                               "worldmap4"};
        QString mapPath = ":/resources/world_images/";
        QString getMapPath(QString mapName) {
            return mapPath + mapName + ".png";
        }

        bool alive = true;
        bool win = false;

        std::unique_ptr<CommandController> commandController;
        std::unique_ptr<MapController> mapController;
        std::unique_ptr<MovementController> movementController;
        std::unique_ptr<PathfindingController> pathfindingController;

        std::unique_ptr<TextView> textView;
        std::unique_ptr<GraphicalView> graphicalView;

        std::shared_ptr<World> newMap;
        std::shared_ptr<WorldModel> world;

        QTimer delayTimer;
        QString terminalOut;
        int animationSpeed;
};