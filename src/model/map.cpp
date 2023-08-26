#include "Map.h"

Map::Map(const std::string& path, int startX, int startY, int endX, int endY)
    : mapPath(path), startX(startX), startY(startY), endX(endX), endY(endY) {}

int Map::getStartX() const {
    return startX;
}

int Map::getStartY() const {
    return startY;
}

int Map::getEndX() const {
    return endX;
}

int Map::getEndY() const {
    return endY;
}
