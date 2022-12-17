#include "graphicalview.h"
#include "QtWidgets/qgraphicsitem.h"
#include <iostream>
#include "ImageWidget.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>

GraphicalView::GraphicalView(){

}

void GraphicalView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> graphicsView){
    this->height=w->getHeight();
    this->width=w->getWidth();
    startposX=w->getProtagonist()->getXPos();
    startposY=w->getProtagonist()->getYPos();
    this->world=w;
    std::cout.flush();
    std::cout << "height:" << this->height << "width:" << this->width << std::endl;
    auto enemies = w->getEnemies();
    auto healthPacks = w->getHealthPacks();
    auto protagonist = w->getProtagonist();
    auto tiles = w->getTiles();

    this->graphicsscene = new QGraphicsScene;
//    graphicsscene->addRect(QRect(0, 0, height, width));
    auto scene = std::make_shared<QGraphicsScene>();
    graphicsView->setScene(scene.get());

    auto proxy = std::make_shared<QGraphicsProxyWidget>();
    auto imageWidget = new ImageWidget();
    QString init_worldmap = ":/images/world_images/maze1.png";
    imageWidget->setImage(QPixmap(init_worldmap));
    proxy->setWidget(imageWidget);

    scene->addItem(proxy.get());
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

}
