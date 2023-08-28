// map.h
#ifndef MAP_H
#define MAP_H

#include <QString>

class Map {
public:
    Map(QString mapPath, QString mapName, int startX, int startY, int endX, int endY);
    Map(QString mapPath, QString mapName);
    Map(QString mapPath);

    int getStartX() const;
    int getStartY() const;
    int getEndX() const;
    int getEndY() const;
    QString getPath() const;
    QString getName() const;

    void setStartX(int x);
    void setStartY(int y);
    void setEndX(int x);
    void setEndY(int y);
    void setPath(QString path);
    void setName(QString name);

private:
    QString mapName;
    QString mapPath;
    int startX;
    int startY;
    int endX;
    int endY;
};

#endif  // MAP_H
