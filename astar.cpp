#include "astar.h"
#include <iostream>

// A* search function that returns a path to the end position from the start position
//vector<pair<int, int> > astar(vector<vector<int> >& grid, int sx, int sy, int ex, int ey){
vector<pair<int, int> > astar(vector< unique_ptr<Tile> >& world_grid, int rows, int cols, Tile start, Tile end){


    vector<vector<int> > grid(rows, vector<int>(cols));

    // Set the grid elements
    for (int row = 0; row < rows; row++){
        for (int col = 0; col < cols; col++){
            grid[row][col] = world_grid[row * cols + col]->getValue();
        }
    }
    // TODO:
    // check if having the end and start positions as variables is quicker than calling them
    int sx = start.getXPos();
    int sy = start.getYPos();
    int ex = end.getXPos();
    int ey = end.getYPos();

    vector<vector<int> > dist(rows, vector<int>(cols, -1)); // distances of each cell from the start position
    vector<vector<pair<int, int> > > path(rows, vector<pair<int, int> >(cols)); // path to reach each cell from the start position
    priority_queue<Node, vector<Node>, NodeComparator> pq; // priority queue of Node objects

    // Initialize the priority queue with the start position and its cost
    pq.push(Node(sx, sy, grid[sx][sy]));
    dist[sx][sy] = grid[sx][sy];

    cout<< "Searching";

    // While the priority queue is not empty
    while(!pq.empty()){
        // Get the top node (node with the lowest cost) from the queue
        Node curr = pq.top();
        pq.pop();

        // If the current node is the end position, return the path to the end position
        if(curr.x == ex && curr.y == ey){
            vector<pair<int, int> > result;
            while(curr.x != sx || curr.y != sy){
                result.push_back(make_pair(curr.x, curr.y));
                curr = Node(path[curr.x][curr.y].first, path[curr.x][curr.y].second,
                        grid[path[curr.x][curr.y].first][path[curr.x][curr.y].second]);
            }
            result.push_back(make_pair(sx, sy));
            reverse(result.begin(), result.end());
            return result;
        }

        // Explore the four possible moves from the current position (right, left, up, down)
        vector<pair<int, int> > moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        for(auto move : moves){
            int nx = curr.x + move.first; // New x-coordinate
            int ny = curr.y + move.second; // New y-coordinate
            // Skip the move if the new position is outside the grid
            if(nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
            // Update the minimum cost and the priority queue if the new position has a lower cost
            if(dist[nx][ny] == -1 || dist[nx][ny] > dist[curr.x][curr.y] + grid[nx][ny]){
                dist[nx][ny] = dist[curr.x][curr.y] + grid[nx][ny];
                pq.push(Node(nx, ny, dist[nx][ny]));
                path[nx][ny] = make_pair(curr.x, curr.y);
            }
        }
    }

    // If we reach here, it means that there is no path from the start position to the end position
    std::cout<< "No path found" << std::endl;
    return {};
}
