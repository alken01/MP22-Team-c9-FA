#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include "textview.h"
#include "world.h"
#include <QObject>
#include <QWidget>

class WorldModel
{
public:
    WorldModel(std::shared_ptr<World> w);

private:
  std::shared_ptr<World> world;
  std::shared_ptr<TextView> text_view;
  std::vector<std::unique_ptr<Tile>> tiles;
  int width;
  int height;
  QVector<QString> qVec;
  std::shared_ptr<QString> stringWorld;
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<std::unique_ptr<Tile>> healthPacks;
  std::unique_ptr<Tile> protagonist;

};

#endif // WORLDMODEL_H
