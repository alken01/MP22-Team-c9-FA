#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "QtWidgets/qmainwindow.h"
#include "graphicalview.h"
#include "textview.h"
#include <QObject>
#include <QWidget>

class Controller {
public:
  Controller(std::shared_ptr<GraphicalView> graphical_view, std::shared_ptr<TextView> text_view);
  void handleInput();
  void update();
  void autoPlay(); // implement a*


  QGraphicsScene* getScene() const;

public slots:
  void switchToGraphic();
  void switchToText();
  void movePlayer(QString direction);
  void switchViews();


private:

  std::shared_ptr<GraphicalView> graphical_view;
  std::shared_ptr<TextView> text_view;


};
#endif // CONTROLLER_H
