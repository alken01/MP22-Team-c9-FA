#ifndef MAP_H
#define MAP_H

#include <QString>
#include <vector>

class Map {
    public:
        Map(QString mapPath, QString mapName, int startX, int startY, int endX,
            int endY) {
            this->mapPath = mapPath;
            this->mapName = mapName;
            this->startX = startX;
            this->startY = startY;
            this->endX = endX;
            this->endY = endY;
        }

        Map(QString mapPath, QString mapName) {
            this->mapPath = mapPath;
            this->mapName = mapName;
            this->startX = -1;
            this->startY = -1;
            this->endX = -1;
            this->endY = -1;
        }

        Map(QString mapPath) {
            this->mapPath = mapPath;
            this->mapName = "";
            this->startX = -1;
            this->startY = -1;
            this->endX = -1;
            this->endY = -1;
        }

        int getStartX() const { return startX; }
        int getStartY() const { return startY; }
        int getEndX() const { return endX; }
        int getEndY() const { return endY; }
        QString getPath() const { return mapPath; }
        QString getName() const { return mapName; }

        void setStartX(int x) { startX = x; }
        void setStartY(int y) { startY = y; }
        void setEndX(int x) { endX = x; }
        void setEndY(int y) { endY = y; }
        void setPath(QString path) { mapPath = path; }
        void setName(QString name) { mapName = name; }

    private:
        QString mapName;
        QString mapPath;
        int startX;
        int startY;
        int endX;
        int endY;
};

#endif  // MAP_H
