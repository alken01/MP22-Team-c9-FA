#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"
#include "worldmodel.h"

class TextView : public View
{
public:
    TextView();

 void changeSignAtCoord( unsigned long x,  unsigned long y, QChar input);
 void draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView);
 void createMap();
 void movProtagonist(std::unique_ptr<Tile>& protagonist);
 void updateView(std::shared_ptr<QGraphicsView> textView);

private:
 QVector<QString> qVec;
 std::shared_ptr<QString> stringWorld;
 int width;
 int height;
 QGraphicsScene* textscene;
 };

#endif // TEXTVIEW_H
