#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include "view.h"
#include "world.h"
#include "worldmodel.h"
#include <QTimer>

class TextView: public View
{
public:
    TextView();

    void changeSignAtCoord(unsigned long x, unsigned long y, QChar input);
    void draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView);
    void createMap();
    void movProtagonist(int x1, int y1, int x2, int y2);
    void updateView();
    void protDead(int x, int y);
    void togglePoisoned();
    void activatePoisoned();
    void startTimer();
    void stopTimer();


private:
 QVector<QString> qVec,qVecPlayer;
 std::shared_ptr<QString> stringWorld;
 std::shared_ptr<QString> playerString;
 std::shared_ptr<QGraphicsView> outputView;
 int width;
 int height;
 QGraphicsScene* textscene;
 QTimer timer;
 int toggle;
 std::shared_ptr<WorldModel> world;
 void moveCamera();
 int renderWidth, renderHeight;
 int xRatio;
 int yRatio;
 int startposX,startposY;
 };

#endif // TEXTVIEW_H
