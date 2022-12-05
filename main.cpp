#include "astar.h"
#include <iostream>
#include <vector>
#include <chrono> // provides classes and functions for measuring time

using namespace std;

int main(){

    // Generate the world
    QString init_worldmap = ":/images/world_images/worldmap4.png";
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

    cout<< "val at 100x100" << world_grid[100*100].get()->getValue() << std::endl;

    Tile start(0,0,0.0);
    Tile end(100,100,0.0);


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

    return 0;
}


