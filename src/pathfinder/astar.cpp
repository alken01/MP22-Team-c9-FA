#include "astar.h"

#include <iostream>

#include "worldmodel.h"

// A* search function that returns a path to the end position from the start
// position
vector<pair<int, int>> astar(shared_ptr<WorldModel>& world, Tile start,
                             Tile end, float white_value) {
    cout << "Starting algo..." << endl;
    // TODO:
    // check if having the end and start positions as variables is quicker than
    // calling them
    int sx = start.getXPos();
    int sy = start.getYPos();
    int ex = end.getXPos();
    int ey = end.getYPos();

    int cols = world->getWidth();
    int rows = world->getHeight();

    vector<vector<float>> grid(cols, vector<float>(rows));

    // Set the grid elements
    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            grid[col][row] = world->getTileValue(col, row);
            if (world->getTileValue(col, row) != INFINITY)
            {
                if (white_value > 0.99)
                {
                    grid[col][row] = 1;
                }
                else
                {
                    grid[col][row] =
                        1 + white_value -
                        grid[col][row];  // if it is not infinte, flip the value
                                         // around, whiter tiles << darker tiles
                }
            }
        }
    }

    vector<vector<float>> dist(
        rows, vector<float>(
                  cols, -1));  // distances of each cell from the start position
    vector<vector<pair<int, int>>> path(
        rows, vector<pair<int, int>>(
                  cols));  // path to reach each cell from the start position
    priority_queue<Node, vector<Node>, NodeComparator>
        pq;  // priority queue of Node objects

    // Initialize the priority queue with the start position and its cost
    pq.push(Node(sx, sy, grid[sx][sy]));
    dist[sx][sy] = grid[sx][sy];

    // Explore the four possible moves from the current position (right, left,
    // up, down)
    vector<pair<int, int>> result = {};

    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // While the priority queue is not empty
    while (!pq.empty())
    {
        // Get the top node (node with the lowest cost) from the queue
        Node curr = pq.top();
        pq.pop();

        // If the current node is the end position, return the path to the end
        // position
        if (curr.x == ex && curr.y == ey)
        {
            pair<int, int> start = make_pair(curr.x, curr.y);
            while (start.first != sx || start.second != sy)
            {
                result.push_back(start);
                start = make_pair(path[start.first][start.second].first,
                                  path[start.first][start.second].second);
            }
            result.push_back(make_pair(sx, sy));
            reverse(result.begin(), result.end());
            break;
        }

        for (auto move : moves)
        {
            int nx = curr.x + move.first;   // New x-coordinate
            int ny = curr.y + move.second;  // New y-coordinate

            // Skip the move if the new position is outside the grid
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                continue;
            if (grid[nx][ny] == INFINITY)
                continue;

            // Update the minimum cost and the priority queue if the new
            // position has a lower cost
            if (dist[nx][ny] == -1 ||
                dist[nx][ny] > dist[curr.x][curr.y] + grid[nx][ny])
            {
                dist[nx][ny] = dist[curr.x][curr.y] + grid[nx][ny];
                pq.push(Node(nx, ny, dist[nx][ny]));
                path[nx][ny] = make_pair(curr.x, curr.y);
            }
        }
    }

    // If we reach here, it means that there is no path from the start position
    // to the end position
    if (result.size() == 0)
        cout << "No path found" << endl;
    return result;
}
