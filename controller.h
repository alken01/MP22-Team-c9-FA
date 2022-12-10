#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "QtWidgets/qmainwindow.h"
#include "graphicalview.h"
#include "textview.h"
#include "worldmodel.h"
#include <QObject>
#include <QWidget>

class Controller {
public:
  Controller(std::shared_ptr<WorldModel> w, std::shared_ptr<GraphicalView> graphical_view, std::shared_ptr<TextView> text_view);
  void handleInput();
  void update();
  void autoPlay(); // implement a*

std::shared_ptr<QGraphicsScene> getScene() const;

const std::shared_ptr<TextView> &getText_view() const;
void setText_view(const std::shared_ptr<TextView> &newText_view);

const std::shared_ptr<QGraphicsView> &getQtext_view() const;
void setQtext_view(const std::shared_ptr<QGraphicsView> &newQtext_view);

public slots:
  void switchToGraphic();
  void switchToText();
  void movePlayer(int direction);
  void switchViews();
  void initWorlds();


private:
  std::shared_ptr<WorldModel> world;
  std::shared_ptr<GraphicalView> graphical_view;
  std::shared_ptr<TextView> text_view;
  std::shared_ptr<QGraphicsView> Qtext_view;

};
#endif // CONTROLLER_H
