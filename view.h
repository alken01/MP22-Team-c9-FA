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
    virtual void draw() = 0;
};


#endif // VIEW_H
