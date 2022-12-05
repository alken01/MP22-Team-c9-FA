#include "astar.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    // Generate the world
    QString init_worldmap = ":/images/world_images/maze2.png";
    World world;
    world.createWorld(init_worldmap, 5,5,0.25);
    int rows = world.getRows();
    int cols = world.getCols();
    vector< unique_ptr<Tile> > world_grid = world.getTiles();

    vector<vector<int> > grid(rows, vector<int>(cols));

    // Set the grid elements
    for(unsigned long i=0;i<world_grid.size();i++){
        grid[i%cols][i%rows] = world_grid[i]->getValue();
        cout<< grid[i%cols][i%rows];
    }



//    // Set the start
//    auto start = world_grid[1];
//    auto end = world_grid[10];

//    // Call the A* search function and print the result to standard output
//    vector<pair<int, int>> path = astar(world_grid,rows,cols, start, end);
//    cout<< "Path:\n";

    return 0;
}
