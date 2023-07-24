#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "world.h"
#include <QObject>
#include <QWidget>

class WorldModel
{
public:
  WorldModel(std::shared_ptr<World> w, int xEnemies);

  const std::vector<std::shared_ptr<Tile> >& getTiles() const;
  void setTiles(const std::vector<std::shared_ptr<Tile> >& newTiles);

  int getWidth() const;
  void setWidth(int newWidth);

  int getHeight() const;
  void setHeight(int newHeight);

  const std::vector<std::shared_ptr<Enemy> >& getEnemies() const;
  void setEnemies(const std::vector<std::shared_ptr<Enemy> >& newEnemies);

  const std::vector<std::shared_ptr<Tile> >& getHealthPacks() const;
  void setHealthPacks(const std::vector<std::shared_ptr<Tile> >& newHealthPacks);

  const std::shared_ptr<Protagonist>& getProtagonist() const;
  void setProtagonist(const std::shared_ptr<Protagonist>& newProtagonist);

  const std::vector<std::vector<std::shared_ptr<Tile> > >& getWorldMap() const;
  void setWorldMap(const std::vector<std::vector<std::shared_ptr<Tile> > >& newWorldMap);

  float getTileValue(int x, int y);

private:
  std::vector<std::shared_ptr<Tile>> tiles;
  int width;
  int height;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::vector<std::shared_ptr<Tile>> healthPacks;
  std::shared_ptr<Protagonist> protagonist;
  std::vector<std::vector<std::shared_ptr<Tile>>> worldMap;
  void initMapVec();
};

#endif // WORLDMODEL_H
