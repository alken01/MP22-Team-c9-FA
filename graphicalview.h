#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H


#include "view.h"

class graphicalview : public View
{
public:
    // Constructor
    graphicalview ();

    // Destructor
    ~graphicalview();

    // Update the view
    void update();

private:
    // Graphics scene for drawing the game world
    std::shared_ptr<QGraphicsScene> scene;

};


#endif // GRAPHICALVIEW_H
