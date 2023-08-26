#ifndef COORDINATES_H
#define COORDINATES_H

#include <functional>

class Coordinates {
public:
    Coordinates() : xPos(0), yPos(0) {}
    Coordinates(int xPos, int yPos) : xPos(xPos), yPos(yPos) {}

    bool operator==(const Coordinates& other) const {
        return xPos == other.xPos && yPos == other.yPos;
    }

    int getX() const { return xPos; }
    int getY() const { return yPos; }
    void setX(int newX) { xPos = newX; }
    void setY(int newY) { yPos = newY; }

private:
    int xPos;
    int yPos;
};

namespace std {
template <>
struct hash<Coordinates> {
    size_t operator()(const Coordinates& coords) const {
        return hash<int>()(coords.getX()) ^ hash<int>()(coords.getY());
    }
};
}  // namespace std

#endif  // COORDINATES_H
