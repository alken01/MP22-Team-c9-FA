#include "graphicalview.h"

GraphicalView::GraphicalView()
{

}

void GraphicalView::draw(int width,int height,std::unique_ptr<Tile>& protagonist,std::vector<std::unique_ptr<Enemy>>& enemies,std::vector<std::unique_ptr<Tile>>& healthPacks,QGraphicsScene scene,std::vector<std::unique_ptr<Tile>>& tiles){
  // Iterate over the tiles in the grid-based map
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {

        scene.addRect(i, j, 50, 50);
    }
  }
}
