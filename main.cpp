#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "mainwindow.h"
#include "world.h"
#include "controller.h"
#include "graphicalview.h"
#include "textview.h"
#include "astar.h"
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include <chrono> 
#include "ImageWidget.h"

using namespace std;

// int main(int argc, char* argv[]){

//     QApplication app(argc, argv);
//     QString init_worldmap = ":/images/world_images/maze2.png";
//     MainWindow w = MainWindow(NULL, init_worldmap);
//     auto test = std::make_shared<World>();
//     test->createWorld(init_worldmap, 5, 5, 0.25);
//     auto gview = std::make_shared<GraphicalView>();
//     auto tview = std::make_shared<TextView>();
//     auto wm = std::make_shared<WorldModel>(test);
//     auto c= std::make_shared<Controller>(wm,gview,tview);
//     c->initWorlds();
//     w.setController(c);

//     w.show();
//     return app.exec();

// }

// TODO:
// Still need to properly merge this, have some functions here be part of the Controller class
int main(int argc, char* argv[]){
    // Generate the world
    QApplication app(argc, argv);
    QString init_worldmap = ":/images/world_images/maze2.png";
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 10, 10, 0.50);
    auto gview = std::make_shared<GraphicalView>();
    auto tview = std::make_shared<TextView>();
    auto wm = std::make_shared<WorldModel>(test);
    auto c= std::make_shared<Controller>(wm,gview,tview);
    c->initWorlds();
    MainWindow w = MainWindow(NULL, init_worldmap, c);
    w.show();

    return app.exec();
}
