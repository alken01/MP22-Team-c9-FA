#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include "view.h"
#include <QObject>
#include <QWidget>

class GraphicalView : public View
{

public:
    GraphicalView();
    void handleInput();
    void update();
    void draw(int width,int height,std::unique_ptr<Tile> protagonist,std::vector<std::unique_ptr<Enemy>> enemies,std::vector<std::unique_ptr<Tile>> healthPacks);
};

#endif // GRAPHICALVIEW_H




