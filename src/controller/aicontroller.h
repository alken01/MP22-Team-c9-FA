#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include <iostream>
#include <memory>
#include "astar.h"
#include "commandsmap.h"
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"

class AIController {
    public:
        AIController(std::shared_ptr<WorldModel> world);
        void setWhiteValue(float newWhiteValue) { whiteValue = newWhiteValue; }

        void getPath(int x, int y);
        int goToEnemy();
        int goToHealthpack();
        void gotoHelper(QString input);
        std::vector<QString> pathToText(std::vector<std::pair<int, int>> path);
        void goToPath(std::vector<std::pair<int, int>> path);
        float pathCost(std::vector<std::pair<int, int>> path);
        void autoPlayLoop();
        void autoPlay();
        void makePathMoves(vector<QString> textPath);
        void setAnimationSpeed(int newSpeed) { animationSpeed = newSpeed; }

    private:
        std::shared_ptr<WorldModel> world;
        float whiteValue;
        int animationSpeed;
        int move;
};

#endif  // AI_CONTROLLER_H