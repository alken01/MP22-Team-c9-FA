#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <QStringList>
#include <QTimer>
#include <iostream>
#include <vector>
#include "astar.h"
#include "worldmodel.h"

class AIController {
    public:
        AIController(std::shared_ptr<WorldModel> world);

        std::vector<QString> gotoHelper(QString input);
        int goToHealthpack();
        int goToEnemy();
        std::vector<QString> getPath(int x, int y);
        void autoPlay();
        void autoPlayLoop();

        void setWhiteValue(float whiteValue);
        void setAnimationSpeed(int animationSpeed);
        int getAnimation();
        void setWorld(std::shared_ptr<WorldModel> world);

    private:
        std::shared_ptr<AStar> astar;
        std::shared_ptr<WorldModel> world;
        float whiteValue;
        int animationSpeed;
        int move;
        float pathCost(const std::vector<std::pair<int, int>>& path);
        void goToPath(const std::vector<std::pair<int, int>>& path);
        void makePathMoves(const std::vector<QString>& textPath);
        std::vector<QString> pathToText(
        const std::vector<Coordinates> path);
};

#endif  // AICONTROLLER_H
