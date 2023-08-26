#ifndef TEXTVIEW_H
#define TEXTVIEW_H
#include <QFontMetrics>
#include <QTimer>
#include "view.h"
#include "coordinates.h"
#include "worldmodel.h"

class TextView : public View {
    public:
        TextView();

        void draw(std::shared_ptr<WorldModel> worldModel,
                  std::shared_ptr<QGraphicsView> textView);
        void moveProtagonist();
        void updateView();
        void protagonistDies();
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
        void changeSignAtCoord(Coordinates coord, QChar input);
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
        std::shared_ptr<WorldModel> worldModel;
};

#endif  // TEXTVIEW_H
