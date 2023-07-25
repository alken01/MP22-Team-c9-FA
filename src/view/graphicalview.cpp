#include "graphicalview.h"

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <iostream>

#include "QtWidgets/qgraphicsitem.h"
#include "image_widget.h"

GraphicalView::GraphicalView() {}

void GraphicalView::draw(std::shared_ptr<WorldModel> w,
                         std::shared_ptr<QGraphicsView> graphicsView) {
    height = w->getHeight();
    width = w->getWidth();
    startposX = w->getProtagonist()->getXPos();
    startposY = w->getProtagonist()->getYPos();
    world = w;
    auto enemies = w->getEnemies();
    auto healthPacks = w->getHealthPacks();
    auto protagonist = w->getProtagonist();
    auto tiles = w->getTiles();

    graphicsscene = new QGraphicsScene;
    //    graphicsscene->addRect(QRect(0, 0, height, width));
    auto scene = std::make_shared<QGraphicsScene>();
    graphicsView->setScene(scene.get());

    auto proxy = std::make_shared<QGraphicsProxyWidget>();
    auto imageWidget = new ImageWidget();
    QString init_worldmap = ":/images/resources/world_images/worldmap.png";
    imageWidget->setImage(QPixmap(init_worldmap));
    proxy->setWidget(imageWidget);

    scene->addItem(proxy.get());
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
