#include "graphicalview.h"
#include "QtWidgets/qgraphicsitem.h"

GraphicalView::GraphicalView(){

}

void GraphicalView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> textView){
    graphicsscene->addItem(worldPix.get());
}
