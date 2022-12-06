#ifndef VIEW_H
#define VIEW_H

#include "world.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>


class View : public QGraphicsView{
    Q_OBJECT
public:
    ~View(){};
    virtual void draw(int width,int height,std::unique_ptr<Tile>& protagonist,std::vector<std::unique_ptr<Enemy>> & enemies,std::vector<std::unique_ptr<Tile>>& healthPacks,QGraphicsScene scene,std::vector<std::unique_ptr<Tile>>& tiles) = 0;
};


#endif // VIEW_H
