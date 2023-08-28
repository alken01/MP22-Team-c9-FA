#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include <QObject>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QWidget>
#include <iostream>
#include <memory>
#include "coordinates.h"
#include "graphicalview.h"
#include "map.h"
#include "textview.h"
#include "world.h"
#include "worldmodel.h"
#include "xenemy.h"
#include "controller.h"

class ViewController {
    public:
        ViewController(std::shared_ptr<WorldModel> world);
        void drawWorlds();
        void render();
        void poisoned();
        void healed();
        void fighting();
        void dead();


        const std::shared_ptr<QGraphicsView>& getQGraphicsView() const;
        const std::shared_ptr<QGraphicsView>& getQTextView() const;
        void setWorld(std::shared_ptr<WorldModel> world);        

    public slots:
        void switchToGraphic();
        void switchToText();
        void switchViews();
        void changeMap();

    private:
        std::shared_ptr<WorldModel> world;
        std::shared_ptr<GraphicalView> graphicalView;
        std::shared_ptr<TextView> textView;

        std::shared_ptr<QGraphicsView> _QTextView, _QGraphicsView;
        QTimer delayTimer;
        int delaySwitch;
        int move;
        void resetDelay();
};

#endif  // VIEW_CONTROLLER_H