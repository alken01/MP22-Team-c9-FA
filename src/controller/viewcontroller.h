#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <memory>
#include "coordinates.h"
#include "graphicalview.h"
#include "map.h"
#include "textview.h"
#include "world.h"
#include "worldmodel.h"
#include "xenemy.h"
#include "controller.h"

class ViewController {
    public:
        ViewController(std::shared_ptr<Controller> controller);
        void drawWorlds();
        void handleInput();
        void update();
        void updateViews();
        void fightEnemy(std::shared_ptr<Enemy> enemy);

        // const std::vector<Map>& getMapList() const;
        const QStringList getMapList() const;
        const std::shared_ptr<WorldModel>& getWorld() const;
        const std::shared_ptr<QGraphicsView>& getQGraphicsView() const;
        const std::shared_ptr<QGraphicsView>& getQTextView() const;
        void setAnimationSpeed(int newSpeed);

    public slots:
        void switchToGraphic();
        void switchToText();
        void switchViews();
        void initWorlds();
        void commandReceived(QString input);
        void changeMap(QString mapName);
        void restart();

    private:
        QStringList mapList = {"maze1", "maze2", "maze3", "worldmap",
                               "worldmap4"};
        QString mapPath = ":/resources/world_images/";
        QString getMapPath(QString mapName) {
            return mapPath + mapName + ".png";
        }
        const unsigned int ViewENEMY_NR = 50;
        const unsigned int HEALTHPACK_NR = 5;
        const float P_RATIO = 0.25f;
        const unsigned int XENEMY_NR = 3;

        int POISON_DAMAGE = 5;
        int POISON_RESISTANCE_PER_TURN = 1;
        int MAX = 100;

        // std::vector<Map> mapList;

        std::shared_ptr<WorldModel> world;
        std::shared_ptr<GraphicalView> graphicalView;
        std::shared_ptr<TextView> textView;

        std::shared_ptr<QGraphicsView> _QTextView, _QGraphicsView;
        QTimer delayTimer;
        std::shared_ptr<World> newMap;
        int animationSpeed;
        int delaySwitch;
        std::shared_ptr<Controller> controller;

        void initializeWorld();
        void dead();
        void printHelp();
        void fightingView();
        void resetDelay();
};

#endif  // VIEW_CONTROLLER_H