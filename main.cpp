#include "astar.h"
#include <iostream>

using namespace std;

int main(){
    // Create a grid with specified dimensions
    int n = 5;
    int m = 5;
    vector<vector<int> > grid(n, vector<int>(m));

    // Set the grid elements
    grid[0][0] = 1; grid[0][1] = 2; grid[0][2] = 3; grid[0][3] = 4; grid[0][4] = 5;
    grid[1][0] = 6; grid[1][1] = 7; grid[1][2] = 8; grid[1][3] = 9; grid[1][4] = 10;
    grid[2][0] = 11; grid[2][1] = 12; grid[2][2] = 13; grid[2][3] = 14; grid[2][4] = 15;
    grid[3][0] = 16; grid[3][1] = 17; grid[3][2] = 18; grid[3][3] = 19; grid[3][4] = 20;
    grid[4][0] = 21; grid[4][1] = 22; grid[4][2] = 23; grid[4][3] = 24; grid[4][4] = 25;

    // Set the start
    int sx = 0;
    int sy = 0;

    // end positions
    int ex = 4;
    int ey = 4;

    // Call the A* search function and print the result to standard output
    vector<pair<int, int> > path = astar(grid, sx, sy, ex, ey);
    for(auto pos : path){
        std::cout << pos.first << ", " << pos.second << std::endl;
    }
    return 0;
}
