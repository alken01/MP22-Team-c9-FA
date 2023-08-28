#ifndef ASTAR_H
#define ASTAR_H

#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>
#include "coordinates.h"
#include "worldmodel.h"

class AStar {
    public:
        AStar(std::shared_ptr<WorldModel> world);

        void setWorld(std::shared_ptr<WorldModel>& world);

        std::vector<Coordinates> findPath(Coordinates start, Coordinates end,
                                          float white_value);

    private:
        struct Node {
                Coordinates coordinates;
                float cost;
                float heuristic;

                Node(const Coordinates coords, float gCost, float hCost);

                float getTotalCost() const;
        };

        struct CompareNode {
                bool operator()(const Node& a, const Node& b);
        };

        float calculateHeuristic(const Coordinates current,
                                 const Coordinates end);
        float calculateCost(const Coordinates from, const Coordinates to);

        std::shared_ptr<WorldModel> world;
};

#endif  // ASTAR_H
