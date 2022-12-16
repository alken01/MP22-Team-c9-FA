#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include <QObject>
#include <QWidget>
#include <QTimer>
#include "QTime"

// should we namespace std; everything?
using namespace std;
class Controller {
public:
    Controller(std::shared_ptr<WorldModel> w);
    void handleInput();
    void update();
    void autoPlay(); // implement a*

    std::shared_ptr<QGraphicsScene> getScene() const;

    const std::shared_ptr<TextView>& getText_view() const;
    void setText_view(const std::shared_ptr<TextView>& newText_view);

    const std::shared_ptr<QGraphicsView>& getQtext_view() const;
    void setQtext_view(const std::shared_ptr<QGraphicsView>& newQtext_view);

    const std::shared_ptr<WorldModel>& getWorld() const;
    void setWorld(const std::shared_ptr<WorldModel>& newWorld);

    int getAlive() const;
    void setAlive(int newAlive);

    int getPoisoned() const;
    void setPoisoned(int newPoisoned);

    const std::shared_ptr<QGraphicsView>& getQgraphics_view() const;
    void setQgraphics_view(const std::shared_ptr<QGraphicsView>& newQgraphics_view);

    const std::vector<QString>& getCommands() const;
    void setCommands(const std::vector<QString>& newCommands);

    const QStringList& getCompleterList() const;
    void setCompleterList(const QStringList& newCompleterList);

    void goto_helper(QString input);
    void goToPath(int x, int y);
    void goToEnemy();
    void goToHealthpack();
    vector<QString> pathToText(vector<pair<int, int> > path);

const QStringList &getMapList() const;
void setMapList(const QStringList &newMapList);

const QString &getTerminalOut() const;
void setTerminalOut(const QString &newTerminalOut);

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
    std::shared_ptr<WorldModel> world;
    std::shared_ptr<GraphicalView> graphical_view;
    std::shared_ptr<TextView> text_view;
    std::shared_ptr<QGraphicsView> Qtext_view, Qgraphics_view;
    int checkMove(int x, int y);
    void dead(int x, int y);
    int alive = 1;
    int poisoned = 0;
    std::vector<QString> commands;
    QStringList completerList;
    QStringList mapList;
    void printHelp();
    QTimer delayTimer;
    void fighting(int x);
    int delaySwitch;
    void resetDelay();
    QString terminalOut;
    std::shared_ptr<World> newMap;
};
#endif // CONTROLLER_H
