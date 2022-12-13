#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include "view.h"
#include <QObject>
#include <QWidget>

class GraphicalView: public View
{

public:
    GraphicalView();
    void handleInput();
    void update();
    void draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView);


private:
    std::shared_ptr<QString> stringWorld;
    std::shared_ptr<QGraphicsScene> graphicsscene;
    std::shared_ptr<QGraphicsPixmapItem> worldPix;
};

#endif // GRAPHICALVIEW_H




