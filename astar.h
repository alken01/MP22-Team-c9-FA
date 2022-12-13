#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include "world.h"

using namespace std;

struct Node {
    int x, y; // Position on the grid (x, y)
    int cost; // Cost of reaching this position
    Node(int x, int y, int cost) : x(x), y(y), cost(cost){}
};

struct NodeComparator {
    bool operator()(const Node& a, const Node& b){
        return a.cost > b.cost;
    }
};

vector<pair<int, int> > astar(const vector< shared_ptr<Tile> >& world_grid, int rows, int cols, Tile start, Tile end, float white_value);

#endif
