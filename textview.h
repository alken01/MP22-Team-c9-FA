#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"

class TextView : public View
{
public:
    TextView();


 void initTextView(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<World> w);

 void createMap();

 void moveProtagonist(int x, int y, std::shared_ptr<Tile> &tile);

private:
     int x,y;

 };

#endif // TEXTVIEW_H
