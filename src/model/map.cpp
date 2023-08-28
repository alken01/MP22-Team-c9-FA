// map.cpp
#include "map.h"

Map::Map(QString mapPath, QString mapName, int startX, int startY, int endX,
         int endY) {
    this->mapPath = mapPath;
    this->mapName = mapName;
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;
}

Map::Map(QString mapPath, QString mapName) {
    this->mapPath = mapPath;
    this->mapName = mapName;
    this->startX = -1;
    this->startY = -1;
    this->endX = -1;
    this->endY = -1;
}

Map::Map(QString mapPath) {
    this->mapPath = mapPath;
    this->mapName = "";
    this->startX = -1;
    this->startY = -1;
    this->endX = -1;
    this->endY = -1;
}

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
QString Map::getPath() const {
    return mapPath;
}
QString Map::getName() const {
    return mapName;
}

void Map::setStartX(int x) {
    startX = x;
}
void Map::setStartY(int y) {
    startY = y;
}
void Map::setEndX(int x) {
    endX = x;
}
void Map::setEndY(int y) {
    endY = y;
}
void Map::setPath(QString path) {
    mapPath = path;
}
void Map::setName(QString name) {
    mapName = name;
}
