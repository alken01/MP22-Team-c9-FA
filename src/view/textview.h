#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QFontMetrics>
#include <QTimer>
#include "constants.h"
#include "coordinates.h"
#include "view.h"
#include "worldmodel.h"

class TextView : public View {
    public:
        TextView();

        void draw(std::shared_ptr<WorldModel> worldModel,
                  std::shared_ptr<QGraphicsView> textView);
        void renderMap();
        void setHealed();
        void setFighting();
        void setPoisoned();
        void startTimer();
        void stopTimer();

    private:
        void setupTimers();
        void initializeMap();
        void populateWorldMap();
        void updateVisibleMap();
        void combineLinesToString();
        void updateText();
        void updateView();
        void resetBackgroundColor();
        void protagonistDies();
        void changeSignAtCoord(Coordinates coord, QChar input);
        QChar grayscaleToASCII(float intensity);
        void setTextViewState(const QColor& color);

        void populateTiles();
        void populateEnemies();
        void populateHealthPacks();
        void populateProtagonist();

        QVector<QString> vectorMap, visibleVectorMap;
        std::shared_ptr<QString> combinedMap;
        std::shared_ptr<QGraphicsView> outputView;

        QGraphicsScene* textScene;
        QTimer poisonedEffectTimer;
        QTimer healthFightTimer;
        std::shared_ptr<WorldModel> worldModel;
};

#endif  // TEXTVIEW_H
