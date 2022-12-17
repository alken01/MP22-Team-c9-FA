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
    QGraphicsScene* graphicsscene;
    std::shared_ptr<QGraphicsPixmapItem> worldPix;

    QVector<QString> qVec,qVecPlayer;
    std::shared_ptr<QString> playerString;
    std::shared_ptr<QGraphicsView> outputView;
    int width;
    int height;
    std::shared_ptr<WorldModel> world;
    int renderWidth, renderHeight;
    int xRatio;
    int yRatio;
    int startposX,startposY;
};

#endif // GRAPHICALVIEW_H




