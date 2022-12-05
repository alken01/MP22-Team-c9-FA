#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H


#include "view.h"
#include "world.h"

class graphicalview : public View
{
    Q_OBJECT
public:
    // Constructor
    graphicalview (std::shared_ptr<World> world);

    // Destructor
    ~graphicalview();

    // Update the view
    void update();

private:
    // Graphics scene for drawing the game world
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<World> world;
    int width;
    int height;
    QVector<QString> qVec;
    std::shared_ptr<QString> stringWorld;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    std::unique_ptr<Tile> protagonist;


};


#endif // GRAPHICALVIEW_H
