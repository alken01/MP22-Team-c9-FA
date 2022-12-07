#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"

class TextView : public View
{
public:
    TextView();

 void changeSignAtCoord( unsigned long x,  unsigned long y, QChar input);
 void draw(int width,int height,std::unique_ptr<Tile>& protagonist,std::vector<std::unique_ptr<Enemy>>& enemies,std::vector<std::unique_ptr<Tile>>& healthPacks, std::shared_ptr<QGraphicsScene> scene,std::vector<std::unique_ptr<Tile>>& tiles);
 void createMap();
 void movProtagonist(std::unique_ptr<Tile>& protagonist,  std::shared_ptr<QGraphicsScene> scene);

private:
 QVector<QString> qVec;
 std::shared_ptr<QString> stringWorld;
 int width;
 int height;
 };

#endif // TEXTVIEW_H
