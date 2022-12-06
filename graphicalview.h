#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include "view.h"
#include <QObject>
#include <QWidget>

class GraphicalView : public View
{

public:
    GraphicalView();
    void handleInput();
    void update();
};

#endif // GRAPHICALVIEW_H




