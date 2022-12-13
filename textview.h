#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"
#include "worldmodel.h"
#include <QTimer>

class TextView : public View
{
public:
    TextView();

 void changeSignAtCoord( unsigned long x,  unsigned long y, QChar input);
 void draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView);
 void createMap();
 void movProtagonist(int x1, int y1, int x2, int y2);
 void updateView();
 void protDead(int x, int y);

private:
 QVector<QString> qVec;
 std::shared_ptr<QString> stringWorld;
 std::shared_ptr<QGraphicsView> outputView;
 int width;
 int height;
 QGraphicsScene* textscene;

 };

#endif // TEXTVIEW_H
