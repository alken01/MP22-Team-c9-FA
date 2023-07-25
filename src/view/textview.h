#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <QTimer>

#include "view.h"
#include "worldmodel.h"
#include "xenemy.h"
using namespace std;

class TextView : public View
{
    public:
        TextView();

        void changeSignAtCoord(unsigned long x, unsigned long y, QChar input);
        void draw(shared_ptr<WorldModel> w, shared_ptr<QGraphicsView> textView);
        void createMap();
        void movProtagonist(int x1, int y1, int x2, int y2,
                            shared_ptr<WorldModel> w);
        void updateView();
        void protDead(int x, int y);
        void togglePoisoned();
        void activatePoisoned();
        void startTimer();
        void stopTimer();
        void healed();
        QChar grayscaleToASCII(float intensity);
        void fighting();

    private:
        QVector<QString> qVec, qVecPlayer;
        shared_ptr<QString> stringWorld;
        shared_ptr<QString> playerString;
        shared_ptr<QGraphicsView> outputView;
        int width;
        int height;
        QGraphicsScene* textscene;
        QTimer timer, timer2;
        int toggle;
        shared_ptr<WorldModel> world;
        void moveCamera();
        int renderWidth, renderHeight;
        int xRatio;
        int yRatio;
        int startposX, startposY;
        void resetBg();
};

#endif  // TEXTVIEW_H
