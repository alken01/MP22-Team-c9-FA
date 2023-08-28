#include "astar.h"
#include <limits>  // Include for using std::numeric_limits

vector<pair<int, int>> astar(shared_ptr<WorldModel>& world, Tile start,
                             Tile end, float white_value) {

    int startX = start.getXPos();
    int startY = start.getYPos();
    int endX = end.getXPos();
    int endY = end.getYPos();

    int cols = world->getWidth();
    int rows = world->getHeight();

    const float WHITE_THRESHOLD = 0.99;
    const float MAX_COST = 1.0;
    
    std::cout << "startX: " << startX << std::endl;
    std::cout << "startY: " << startY << std::endl;
    std::cout << "endX: " << endX << std::endl;
    std::cout << "endY: " << endY << std::endl;

    std::cout << "white_value: " << white_value << std::endl;
    vector<vector<float>> grid(cols, vector<float>(rows));

    // Set the grid elements
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            Coordinates coord(col, row);

            float tileValue = world->getTileValue(coord);
            if (tileValue != std::numeric_limits<float>::infinity()) {
                if (white_value > WHITE_THRESHOLD) {
                    grid[col][row] = MAX_COST;
                } else {
                    grid[col][row] = MAX_COST - tileValue; // Flip the value
                }
            } else {
                grid[col][row] = tileValue;
            }
        }
    }


    vector<vector<float>> dist(rows, vector<float>(cols, std::numeric_limits<float>::infinity()));
    vector<vector<pair<int, int>>> path(rows, vector<pair<int, int>>(cols));
    priority_queue<Node, vector<Node>, NodeComparator> pq;

    pq.push(Node(startX, startY, grid[startX][startY]));
    dist[startX][startY] = grid[startX][startY];

    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
    vector<pair<int, int>> result = {};

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.x == endX && curr.y == endY) {
            pair<int, int> position = make_pair(curr.x, curr.y);
            while (position.first != startX || position.second != startY) {
                result.push_back(position);
                position = make_pair(path[position.first][position.second].first,
                                     path[position.first][position.second].second);
            }
            result.push_back(make_pair(startX, startY));
            reverse(result.begin(), result.end());
            break;
        }

        for (auto move : moves) {
            int nx = curr.x + move.first;
            int ny = curr.y + move.second;

            if (nx < 0 || nx >= cols || ny < 0 || ny >= rows) continue;
            if (grid[nx][ny] == std::numeric_limits<float>::infinity()) continue;

            if (dist[nx][ny] == std::numeric_limits<float>::infinity() ||
                dist[nx][ny] > dist[curr.x][curr.y] + grid[nx][ny]) {
                dist[nx][ny] = dist[curr.x][curr.y] + grid[nx][ny];
                pq.push(Node(nx, ny, dist[nx][ny]));
                path[nx][ny] = make_pair(curr.x, curr.y);
            }
        }
    }

    if (result.empty()) cout << "No path found" << endl;
    return result;
}
