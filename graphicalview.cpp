#include "graphicalview.h"
#include "QtWidgets/qgraphicsitem.h"

GraphicalView::GraphicalView()
{

}

void GraphicalView::draw(std::shared_ptr<WorldModel> w, std::shared_ptr<QGraphicsView> graphicsView){
    this->graphicsscene = new QGraphicsScene;
    graphicsscene->addRect(QRectF(0, 0, 100, 100));
    graphicsView->setScene(graphicsscene);
}
