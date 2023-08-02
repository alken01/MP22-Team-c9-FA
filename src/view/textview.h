#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <QFontMetrics>
#include <QTimer>
#include "view.h"
#include "world.h"
#include "worldmodel.h"
#include "xenemy.h"

class TextView : public View {
    public:
        TextView();

        void draw(std::shared_ptr<WorldModel> w,
                  std::shared_ptr<QGraphicsView> textView);
        void moveProtagonist(Tile::Coordinates currentCoord,
                             std::shared_ptr<WorldModel> w);
        void updateView();
        void protagonistDies(Tile::Coordinates coord);
        void setHealed();
        void setFighting();
        void setPoisoned();
        void startTimer();
        void stopTimer();

    private:
        void setupTimers();
        void initializeMap();
        void populateWorldMap();
        void combineLinesToString();
        QChar grayscaleToASCII(float intensity);
        void changeSignAtCoord(Tile::Coordinates coord, QChar input);
        void updateVisibleMap();
        void updateText();
        void resetBackgroundColor();
        void setTextViewState(const QColor& color);

        QVector<QString> vectorMap, visibleVectorMap;
        std::shared_ptr<QString> combinedMap;
        std::shared_ptr<QGraphicsView> outputView;

        QGraphicsScene* textScene;
        QTimer poisonedEffectTimer;
        QTimer healthFightTimer;
        std::shared_ptr<WorldModel> world;
};

#endif  // TEXTVIEW_H
