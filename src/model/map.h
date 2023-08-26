#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
    public:
        Map(const std::string& path, int startX, int startY, int endX,
            int endY);

        int getStartX() const;
        int getStartY() const;
        int getEndX() const;
        int getEndY() const;

    private:
        std::string mapPath;
        int startX;
        int startY;
        int endX;
        int endY;
};

#endif  // MAP_H

// mapList = {"maze1", "maze2", "maze3", "worldmap", "worldmap4"};
// mapPath = ":/resources/world_images/";
