#include "mainwindow.h"
#include "controller.h"
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include <chrono> 
#include "ImageWidget.h"
#include <memory>
#include "astar.h"
#include "worldmodel.h"

using namespace std;
int main(int argc, char* argv[]){

    int choose = 1;
    if(choose == 0){
        QApplication app(argc, argv);
        auto c = std::make_shared<Controller>();
        MainWindow w = MainWindow(NULL, c);
        w.initViews();
        w.show();
        return app.exec();
    }

//    // main for astar testing
    else{
        // Generate the world
        QApplication app(argc, argv);

        int i = 3;

        QString init_worldmap;
        Tile start(0, 0, 1.0);
        Tile end(0, 1, 1.0);

        if(i == 0){
            init_worldmap = ":/images/world_images/worldmap.png";
            start = Tile(3, 5, 1.0);
            end = Tile(29, 5, 1.0);
        }

        if(i == 4){
            init_worldmap = ":/images/world_images/worldmap4.png";
            start = Tile(3, 44, 1.0);
            end = Tile(999, 937, 1.0);
        }


        if(i == 1){
            init_worldmap = ":/images/world_images/maze1.png";
            start = Tile(0, 492, 1.0);
            end = Tile(499, 334, 1.0);
        }

        if(i == 2){
            init_worldmap = ":/images/world_images/maze2.png";
            start = Tile(445, 430, 1.0);
            end = Tile(440, 208, 1.0);
        }
        if(i == 3){
            init_worldmap = ":/images/world_images/maze3.png";
            start = Tile(0, 10, 1.0);
            end = Tile(1146, 1179, 1.0);
        }

        auto test = std::make_shared<World>();
        test->createWorld(init_worldmap, 100, 100, 0.5);
        auto wm = std::make_shared<WorldModel>(test,1);


        int rows = wm->getHeight();
        int cols = wm->getWidth();

        std::cout << "world_grid size: " << cols << "x" << rows << std::endl;

        // Start the timer
        auto start_timer = std::chrono::high_resolution_clock::now();

        // Call the A* search function and
        vector<pair<int, int>> path = astar(wm, start, end, 0.98);


        // Stop the timer
        auto end_timer = std::chrono::high_resolution_clock::now();

        // Only show window if found path
        cout << "Path:\n";

        for (const auto& pair : path)
            std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
        // Calculate the elapsed time in milliseconds
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer);

        // Print the elapsed time
        std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;

        ImageWidget widget;
        widget.setImage(QPixmap(init_worldmap));
        widget.setPath(path);
        widget.show();
        return app.exec();
    }
}
