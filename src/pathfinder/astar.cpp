#include "astar.h"

AStar::AStar(std::shared_ptr<WorldModel> world) : world(world) {}

void AStar::setWorld(std::shared_ptr<WorldModel>& newWorld) {
    world = newWorld;
}

std::vector<Coordinates> AStar::findPath(Coordinates start, Coordinates end,
                                         float white_value) {
    std::vector<Coordinates> path;
    std::priority_queue<Node, std::vector<Node>, CompareNode> openSet;
    std::unordered_map<Coordinates, bool> closedSet;
    std::unordered_map<Coordinates, Coordinates> parentMap;

    openSet.push(Node(start, 0.0f, calculateHeuristic(start, end)));

    // A* algorithm
    while (!openSet.empty()) {
        // Get the node with the lowest cost
        Node current = openSet.top();
        openSet.pop();
        // Check if we have reached the end
        if (current.coordinates == end) {
            Coordinates currentCoords = end;
            // Reconstruct the path
            while (!(currentCoords == start)) {
                // Add the current coordinates to the path
                path.push_back(currentCoords);
                currentCoords = parentMap[currentCoords];
            }
            // Reverse the path so it is in the correct order
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Add the current node to the closed set
        closedSet[current.coordinates] = true;

        // Get the neighbors of the current node
        std::vector<Coordinates> neighbors = {
        {current.coordinates.getX() - 1, current.coordinates.getY()},
        {current.coordinates.getX() + 1, current.coordinates.getY()},
        {current.coordinates.getX(), current.coordinates.getY() - 1},
        {current.coordinates.getX(), current.coordinates.getY() + 1}};

        // Loop through the neighbors
        for (const auto neighbor : neighbors) {
            // Check if the neighbor is out of bounds or in the closed set
            if (!world->isValidCoordinate(neighbor)) continue;

            // Check if the neighbor is in the open set
            if (world->getTileValue(neighbor) < white_value && !closedSet[neighbor]) {
                float newCost =
                current.cost + calculateCost(current.coordinates, neighbor);

                if (newCost < current.cost ||
                    parentMap.find(neighbor) == parentMap.end()) {
                    parentMap[neighbor] = current.coordinates;
                    openSet.push(
                    Node(neighbor, newCost, calculateHeuristic(neighbor, end)));
                }
            }
        }
    }

    std::cerr << "No path found." << std::endl;
    return path;
}

float AStar::calculateCost(const Coordinates from, const Coordinates to) {
    return abs(from.getX() - to.getX()) + abs(from.getY() - to.getY());
}

AStar::Node::Node(const Coordinates coords, float gCost, float hCost)
    : coordinates(coords), cost(gCost), heuristic(hCost) {}

float AStar::Node::getTotalCost() const {
    return cost + heuristic;
}

bool AStar::CompareNode::operator()(const Node& a, const Node& b) {
    return a.getTotalCost() > b.getTotalCost();
}

float AStar::calculateHeuristic(const Coordinates current,
                                const Coordinates end) {
    return abs(current.getX() - end.getX()) + abs(current.getY() - end.getY());
}
