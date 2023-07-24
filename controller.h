#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include "QTime"
#include <memory>
#include <iostream>
#include "astar.h"
#include "xenemy.h"
#include <QPixmap>

using namespace std;
class Controller {
public:
    Controller();
    void handleInput();
    void update();
    void autoPlay();
    int getAlive() const;
    void setAlive(int newAlive);
    int getPoisoned() const;
    void setPoisoned(int newPoisoned);
    void setText_view(const shared_ptr<TextView>& newText_view);
    void setQtext_view(const shared_ptr<QGraphicsView>& newQtext_view);
    void setWorld(const shared_ptr<WorldModel>& newWorld);
    shared_ptr<QGraphicsScene> getScene() const;
    const shared_ptr<TextView>& getText_view() const;
    const shared_ptr<QGraphicsView>& getQtext_view() const;
    const shared_ptr<WorldModel>& getWorld() const;
    const shared_ptr<QGraphicsView>& getQgraphics_view() const;
    void setQgraphics_view(const shared_ptr<QGraphicsView>& newQgraphics_view);
    const vector<QString>& getCommands() const;
    void setCommands(const vector<QString>& newCommands);
    const QStringList& getCompleterList() const;
    void setCompleterList(const QStringList& newCompleterList);
    void getPath(int x, int y);
    int goToEnemy();
    int goToHealthpack();
    void gotoHelper(QString input);
    vector<QString> pathToText(vector<pair<int, int> > path);
    void goToPath(vector<pair<int, int> > path);
    float pathCost(vector<pair<int, int> > path);
    const QStringList& getMapList() const;
    void setMapList(const QStringList& newMapList);
    const QString& getTerminalOut() const;
    void setTerminalOut(const QString& newTerminalOut);
    float getWhiteValue() const;
    void setWhiteValue(float newWhiteValue);
    int getWin() const;
    void setWin(int newWin);
    int getAnimationSpeed() const;
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
    shared_ptr<WorldModel> world;
    shared_ptr<GraphicalView> graphical_view;
    shared_ptr<TextView> text_view;
    shared_ptr<QGraphicsView> Qtext_view, Qgraphics_view;
    int alive = 1;
    int poisoned = 0;
    vector<QString> commands;
    QStringList completerList;
    QStringList mapList;
    QTimer delayTimer;
    QString terminalOut;
    shared_ptr<World> newMap;
    int animationSpeed;
    float whiteValue;
    int enemiesCount;
    int Win;
    unsigned long move, loop;
    int delaySwitch;

    int checkMove(int x, int y);
    void dead(int x, int y);
    void printHelp();
    void fighting();
    void resetDelay();
    void makePathMoves(vector<QString> textPath);
    void autoPlayLoop();
};
#endif // CONTROLLER_H
