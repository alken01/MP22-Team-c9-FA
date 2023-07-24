#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <memory>

#include "QTime"
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

   public:
    int getAlive() const;
    void setAlive(int newAlive);
    int getPoisoned() const;
    const std::shared_ptr<QGraphicsView>& getQtext_view() const;
    const std::shared_ptr<WorldModel>& getWorld() const;
    const std::shared_ptr<QGraphicsView>& getQgraphics_view() const;
    void setQgraphics_view(
        const std::shared_ptr<QGraphicsView>& newQgraphics_view);
    const QStringList& getCommands() const;
    void getPath(int x, int y);
    int goToEnemy();
    int goToHealthpack();
    void gotoHelper(QString input);
    std::vector<QString> pathToText(std::vector<std::pair<int, int>> path);
    void goToPath(std::vector<std::pair<int, int>> path);
    float pathCost(std::vector<std::pair<int, int>> path);
    const QStringList& getMapList() const;
    const QString& getTerminalOut() const;
    void setTerminalOut(const QString& newTerminalOut);
    void setWhiteValue(float newWhiteValue);
    int getWin() const;
    void setAnimationSpeed(int newAnimationSpeed);

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
    QStringList mapList = {"maze1", "maze2", "maze3", "worldmap", "worldmap4"};
    std::shared_ptr<WorldModel> world;
    std::shared_ptr<GraphicalView> graphical_view;
    std::shared_ptr<TextView> text_view;
    std::shared_ptr<QGraphicsView> Qtext_view, Qgraphics_view;
    int alive = 1;
    int poisoned = 0;

    QTimer delayTimer;
    QString terminalOut;
    std::shared_ptr<World> newMap;
    int animationSpeed;
    float whiteValue;
    int enemiesCount;
    int Win;
    std::size_t move, loop;
    int delaySwitch;

   private:
    void initializeWorld();

    int checkMove(int x, int y);
    void dead(int x, int y);
    void printHelp();
    void fighting();
    void resetDelay();
    void makePathMoves(std::vector<QString> textPath);
    void autoPlayLoop();
};

#endif  // CONTROLLER_H
