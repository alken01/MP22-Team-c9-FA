#include "graphicalview.h"
#include "QtWidgets/qgraphicsitem.h"

GraphicalView::GraphicalView()
{

}

void GraphicalView::draw(int width,int height,std::unique_ptr<Tile>& protagonist,std::vector<std::unique_ptr<Enemy>>& enemies,std::vector<std::unique_ptr<Tile>>& healthPacks, std::shared_ptr<QGraphicsScene> scene,std::vector<std::unique_ptr<Tile>>& tiles){
    graphicsscene->addItem(worldPix.get());
}
