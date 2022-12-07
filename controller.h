#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "QtWidgets/qmainwindow.h"
#include "graphicalview.h"
#include "textview.h"
#include <QObject>
#include <QWidget>

class Controller {
public:
  Controller(QMainWindow* window,std::shared_ptr<World> world, std::shared_ptr<GraphicalView> graphical_view, std::shared_ptr<TextView> text_view);
  void handleInput();
  void update();
  void autoPlay(); // implement a*


  QGraphicsScene* getScene() const;

public slots:
  void switchViews();

private:
  std::shared_ptr<World> world;
  std::shared_ptr<GraphicalView> graphical_view;
  std::shared_ptr<TextView> text_view;
  std::vector<std::unique_ptr<Tile>> tiles;
  int width;
  int height;
  QVector<QString> qVec;
  std::shared_ptr<QString> stringWorld;
  QGraphicsScene* scene;
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<std::unique_ptr<Tile>> healthPacks;
  std::unique_ptr<Tile> protagonist;
  bool graph_or_text;
  QMainWindow* window;
};
#endif // CONTROLLER_H
