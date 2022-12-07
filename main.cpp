#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "mainwindow.h"
#include "world.h"
#include "controller.h"
#include "graphicalview.h"
#include "textview.h"
#include <iostream>
#include <Qt>
#include <QApplication>
#include <QPainter>
#include <QtGui>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString init_worldmap = ":/images/world_images/maze2.png";
    MainWindow w = MainWindow(NULL,init_worldmap);
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 5,5,0.25);
    auto gview = std::make_shared<GraphicalView>();
    auto tview = std::make_shared<TextView>();
    auto c= std::make_shared<Controller>(&w,test,gview,tview);
    c->initWorlds();
    w.setController(c);


    w.show();
    return a.exec();


}
