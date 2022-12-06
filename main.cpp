#include "astar.h"
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <vector>
#include <chrono> // provides classes and functions for measuring time
#include "ImageWidget.h"

using namespace std;

int main(int argc, char *argv[]){

    // Generate the world
    QString init_worldmap = ":/images/world_images/worldmap.png";
    World world;
    world.createWorld(init_worldmap, 5,5,0.25);

    // Copy the tiles in world_grid
    std::vector< std::unique_ptr<Tile> > world_grid;
    std::cout << "world_grid size: " << world_grid.size() << std::endl;
    for (auto& ptr : world.getTiles()){
        world_grid.push_back(move(ptr));
    }

    int rows = world.getRows();
    int cols = world.getCols();

    std::cout << "world_grid size: " << rows <<"x"<<cols << std::endl;

    Tile start(3,6,0.0);
    Tile end(16,10,0.0);

    vector<vector<float> > grid(rows, vector<float>(cols));

    // Set the grid elements
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            grid[row][col] = world_grid[row * cols + col]->getValue();
        }
    }
    // Start the timer
    auto start_timer = std::chrono::high_resolution_clock::now();

    // Call the A* search function and
    vector<pair<int, int>> path = astar(world_grid,rows,cols, start, end);

    // Stop the timer
    auto end_timer = std::chrono::high_resolution_clock::now();

    cout<< "Path:\n";
    // Print the result to standard output
    for (const auto& pair : path){
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }

    // Calculate the elapsed time in milliseconds
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer);

    // Print the elapsed time
    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;

    QApplication app(argc, argv);

    // Create the widget
    ImageWidget widget;

    // Set the image
    widget.setImage(QPixmap(init_worldmap));

    // Set the path
    widget.setPath(path);


    // Show the widget
    widget.show();

    return app.exec();
    return 0;
}


