#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"

class TextView : public View
{
public:
    TextView();

 void changeSignAtCoord( unsigned long x,  unsigned long y, QChar input);
 void draw(int width,int height,std::unique_ptr<Tile> protagonist,std::vector<std::unique_ptr<Enemy>> enemies,std::vector<std::unique_ptr<Tile>> healthPacks,std::shared_ptr<QGraphicsScene> scene);
 void createMap();
 void movProtagonist();

private:
 int width;
 int height;
 QVector<QString> qVec;
 std::shared_ptr<QString> stringWorld;
 std::shared_ptr<QGraphicsScene> sc;
 std::shared_ptr<World> world;
 std::vector<std::unique_ptr<Enemy>> enemies;
 std::vector<std::unique_ptr<Tile>> healthPacks;
 std::unique_ptr<Tile> protagonist;




 };

#endif // TEXTVIEW_H
