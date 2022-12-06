#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "graphicalview.h"
#include "textview.h"
#include <QObject>
#include <QWidget>

class Controller {
public:
  Controller(std::shared_ptr<World> world, std::shared_ptr<GraphicalView> graphical_view, std::shared_ptr<TextView> text_view);
  void handleInput();
  void update();
  void autoPlay(); // implement a*


private:
  std::shared_ptr<World> world;
  std::shared_ptr<GraphicalView> graphical_view;
  std::shared_ptr<TextView> text_view;
  int width;
  int height;
  QVector<QString> qVec;
  std::shared_ptr<QString> stringWorld;
  std::shared_ptr<QGraphicsScene> scene;
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<std::unique_ptr<Tile>> healthPacks;
  std::unique_ptr<Tile> protagonist;
  bool graph_or_text;
};
#endif // CONTROLLER_H
