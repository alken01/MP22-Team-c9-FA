#ifndef VIEW_H
#define VIEW_H

#include "world.h"
#include "worldmodel.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>


class View : public QGraphicsView{
    Q_OBJECT
public:
    ~View(){};
    virtual void draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView) = 0;
};


#endif // VIEW_H
