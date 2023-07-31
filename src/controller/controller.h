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

class Controller {
    public:
        Controller();

        void handleInput();
        void update();
        void autoPlay();

        bool isAlive() const { return alive; }
        void setAlive(int newAlive) { alive = newAlive; }
        int getPoisoned() const { return poisoned; }
        const QStringList& getCommands() const { return commands; }
        const QStringList& getMapList() const { return mapList; }
        const QString& getTerminalOut() const { return terminalOut; }
        void setTerminalOut(const QString& newOut) { terminalOut = newOut; }
        bool getWin() const { return win; }
        void setAnimationSpeed(int newSpeed) { animationSpeed = newSpeed; }

        const std::shared_ptr<QGraphicsView>& getQtext_view() const {
            return Qtext_view;
        }
        const std::shared_ptr<WorldModel>& getWorld() const { return world; }
        const std::shared_ptr<QGraphicsView>& getQgraphics_view() const {
            return QgraphicsView;
        }
        void setQgraphics_view(const std::shared_ptr<QGraphicsView>& newView) {
            QgraphicsView = newView;
        }
        void setWhiteValue(float newWhiteValue) { whiteValue = newWhiteValue; }

    private:
        void getPath(int x, int y);
        int goToEnemy();
        int goToHealthpack();
        void gotoHelper(QString input);
        std::vector<QString> pathToText(std::vector<std::pair<int, int>> path);
        void goToPath(std::vector<std::pair<int, int>> path);
        float pathCost(std::vector<std::pair<int, int>> path);

    public slots:
        void switchToGraphic();
        void switchToText();
        void movePlayer(QString input);
        void switchViews();
        void initWorlds();
        QString commandReceived(QString input);
        void changeMap(QString mapName);
        void restart();

    private:
        QStringList commands = {"up",       "down",       "left",    "right",
                                "goto x y", "goto enemy", "goto hp", "help"};
        QStringList mapList = {"maze1", "maze2", "maze3", "worldmap",
                               "worldmap4"};
        QString mapPath = ":/resources/world_images/";
        QString getMapPath(QString mapName) {
            return mapPath + mapName + ".png";
        }

        std::shared_ptr<WorldModel> world;
        std::shared_ptr<GraphicalView> graphical_view;
        std::shared_ptr<TextView> text_view;
        std::shared_ptr<QGraphicsView> Qtext_view, QgraphicsView;
        bool alive = true;
        int poisoned = 0;
        bool win;

        QTimer delayTimer;
        QString terminalOut;
        std::shared_ptr<World> newMap;
        int animationSpeed;
        float whiteValue;
        int enemiesCount;
        std::size_t move, loop;
        int delaySwitch;

    private:
        void initializeWorld();
        int checkMove(int x, int y);
        void dead();
        void printHelp();
        void fighting();
        void resetDelay();
        void makePathMoves(std::vector<QString> textPath);
        void autoPlayLoop();
};