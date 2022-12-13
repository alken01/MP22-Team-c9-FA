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
    QString init_worldmap = ":/images/world_images/maze1.png";
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 3000, 10, 0.10);
    auto gview = std::make_shared<GraphicalView>();
    auto tview = std::make_shared<TextView>();
    auto wm = std::make_shared<WorldModel>(test);
    auto c = std::make_shared<Controller>(wm, gview, tview);
    c->initWorlds();
    MainWindow w = MainWindow(NULL, init_worldmap, c);
    w.show();
    w.setScroll();
    return app.exec();
}

// // main for astar testing
// int main(int argc, char* argv[]){
//     // Generate the world
//     QApplication app(argc, argv);

//     int i = 3;

//     QString init_worldmap;
//     Tile start(0, 0, 1.0);
//     Tile end(0, 1, 1.0);

//     if(i == 0){
//         init_worldmap = ":/images/world_images/worldmap.png";
//         start = Tile(3, 5, 1.0);
//         end = Tile(29, 5, 1.0);
//     }

//     if(i == 4){
//         init_worldmap = ":/images/world_images/worldmap4.png";
//         start = Tile(3, 44, 1.0);
//         end = Tile(999, 937, 1.0);
//     }


//     if(i == 1){
//         init_worldmap = ":/images/world_images/maze1.png";
//         start = Tile(0, 492, 1.0);
//         end = Tile(499, 334, 1.0);
//     }

//     if(i == 2){
//         init_worldmap = ":/images/world_images/maze2.png";
//         start = Tile(445, 430, 1.0);
//         end = Tile(440, 208, 1.0);
//     }
//     if(i == 3){
//         init_worldmap = ":/images/world_images/maze3.png";
//         start = Tile(0, 0, 1.0);
//         end = Tile(1175, 1196, 1.0);
//     }

//     World world;
//     world.createWorld(init_worldmap, 5, 5, 0.25);

//     // Copy the tiles in world_grid
//     std::vector< std::unique_ptr<Tile> > world_grid;
//     for(auto& ptr : world.getTiles()){
//         world_grid.push_back(move(ptr));
//     }

//     int rows = world.getRows();
//     int cols = world.getCols();

//     std::cout << "world_grid size: " << cols << "x" << rows << std::endl;

//     // Start the timer
//     auto start_timer = std::chrono::high_resolution_clock::now();

//     //     Call the A* search function and
//     vector<pair<int, int>> path = astar(world_grid, rows, cols, start, end, 0.1);


//     // Stop the timer
//     auto end_timer = std::chrono::high_resolution_clock::now();

//     // Only show window if found path
//     cout << "Path:\n";
//     //     Print the result to standard output
//     //    for (const auto& pair : path) std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;

//     // Calculate the elapsed time in milliseconds
//     auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer);

//     // Print the elapsed time
//     std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;


//     // Create the widget
//     ImageWidget widget;

//     // Set the image
//     widget.setImage(QPixmap(init_worldmap));

//     // Set the path
//     widget.setPath(path);

//     // Show the widget
//     widget.show();
//     return app.exec();
// }
