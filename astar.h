#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

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

vector<pair<int, int> > astar(vector<vector<int> >& grid, int sx, int sy, int ex, int ey);

#endif