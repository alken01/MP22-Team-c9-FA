#include "astar.h"
#include <iostream>

// A* search function that returns a path to the end position from the start position
vector<pair<int, int> > astar(const vector< shared_ptr<Tile> >& world_grid, int rows, int cols, Tile start, Tile end, float white_value){
    cout << "Starting algo..." << endl;
    // TODO:
    // check if having the end and start positions as variables is quicker than calling them
    int sx = start.getXPos();
    int sy = start.getYPos();
    int ex = end.getXPos();
    int ey = end.getYPos();

    cout << "Start: (" << sx << ", " << sy << ", " << start.getValue() << ")" << endl;
    cout << "End: (" << ex << ", " << ey << ", " << end.getValue() << ")" << endl;
    cout << "Rows/Y:\t" << rows << endl;
    cout << "Cols/X:\t" << cols << endl;

    //    if(sx < 0 || sx >= cols || sy < 0 || sy >= rows){
    //        cout<< "Start value out of bounds"<<endl;
    //        return {};
    //    }
    //    if(ex < 0 || ex >= cols || ey < 0 || ey >= rows){
    //        cout<< "End value out of bounds"<<endl;
    //        return {};
    //    }

    vector<vector<float> > grid(cols, vector<float>(rows));

    // Set the grid elements
    for(int col = 0; col < cols; col++){
        for(int row = 0; row < rows; row++){
            grid[col][row] = world_grid[row * cols + col]->getValue();
        }
    }

    vector<vector<float> > dist(rows, vector<float>(cols, -1)); // distances of each cell from the start position
    vector<vector<pair<int, int> > > path(rows, vector<pair<int, int> >(cols)); // path to reach each cell from the start position
    priority_queue<Node, vector<Node>, NodeComparator> pq; // priority queue of Node objects

    // Initialize the priority queue with the start position and its cost
    pq.push(Node(sx, sy, grid[sx][sy]));
    dist[sx][sy] = grid[sx][sy];

    // Explore the four possible moves from the current position (right, left, up, down)
    vector<pair<int, int> > result = {};

    // TODO: try how it looks with diagonal moves
    // vector<pair<int, int> > moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, 
    //                                  {-1, -1}, {1, 1}, {-1, 1}, {1, -1}  };
    vector<pair<int, int> > moves = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };


    // While the priority queue is not empty
    while(!pq.empty()){
        //        cout<< "Searching..." << endl;
                // Get the top node (node with the lowest cost) from the queue
        Node curr = pq.top();
        pq.pop();

        // If the current node is the end position, return the path to the end position
        if(curr.x == ex && curr.y == ey){

            pair<int, int> start = make_pair(curr.x, curr.y);
            while(start.first != sx || start.second != sy){
                result.push_back(start);
                start = make_pair(path[start.first][start.second].first, path[start.first][start.second].second);
            }
            result.push_back(make_pair(sx, sy));
            reverse(result.begin(), result.end());
            break;
        }

        for(auto move : moves){
            int nx = curr.x + move.first; // New x-coordinate
            int ny = curr.y + move.second; // New y-coordinate

            // Skip the move if the new position is outside the grid
            if(nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
            if(grid[nx][ny] > 1.1) continue;
            if(grid[nx][ny] == 1.0) grid[nx][ny] = white_value;

            // Update the minimum cost and the priority queue if the new position has a lower cost
            if(dist[nx][ny] == -1 || dist[nx][ny] > dist[curr.x][curr.y] + grid[nx][ny]){
                dist[nx][ny] = dist[curr.x][curr.y] + grid[nx][ny];
                pq.push(Node(nx, ny, dist[nx][ny]));
                path[nx][ny] = make_pair(curr.x, curr.y);
            }
        }
    }

    // If we reach here, it means that there is no path from the start position to the end position
    if(result.size() == 0) cout << "No path found" << endl;

    return result;
}
