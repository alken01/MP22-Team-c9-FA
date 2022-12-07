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

int main(int argc, char* argv[]){

    QApplication app(argc, argv);
    QString init_worldmap = ":/images/world_images/maze2.png";
    MainWindow w = MainWindow(NULL, init_worldmap);
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 5, 5, 0.25);
    auto gview = std::make_shared<GraphicalView>();
    auto tview = std::make_shared<TextView>();
    Controller* controller = new Controller(&w, test, gview, tview);

    w.show();
    return app.exec();

}


// TODO:
// Still need to properly merge this, have some functions here be part of the Controller class
// void main_for_the_algo(){
//     // Generate the world
//     QString init_worldmap = ":/images/world_images/maze3.png";
//     World world;
//     world.createWorld(init_worldmap, 5, 5, 0.25);

//     // Copy the tiles in world_grid
//     std::vector< std::unique_ptr<Tile> > world_grid;
//     std::cout << "world_grid size: " << world_grid.size() << std::endl;
//     for(auto& ptr : world.getTiles()){
//         world_grid.push_back(move(ptr));
//     }

//     int rows = world.getRows();
//     int cols = world.getCols();

//     std::cout << "world_grid size: " << rows << "x" << cols << std::endl;

//     Tile start(20, 31, 1.0);
//     Tile end(1175, 1198, 1.0);


//     // Start the timer
//     auto start_timer = std::chrono::high_resolution_clock::now();

//     // Call the A* search function and
//     vector<pair<int, int>> path = astar(world_grid, rows, cols, start, end);

//     // Stop the timer
//     auto end_timer = std::chrono::high_resolution_clock::now();

//     if(!path.empty()){
//         cout << "Path:\n";
//         // Print the result to standard output
// //        for (const auto& pair : path){
// //            std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
// //        }

//         // Calculate the elapsed time in milliseconds
//         auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer);

//         // Print the elapsed time
//         std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;


//         // Create the widget
//         ImageWidget widget;

//         // Set the image
//         widget.setImage(QPixmap(init_worldmap));

//         // Set the path
//         widget.setPath(path);

//         // Show the widget
//         widget.show();
//         return app.exec();
//     } else{
//         return 0;
//     }
// }
