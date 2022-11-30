#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "mainwindow.h"
#include "world.h"
#include <iostream>
#include <Qt>
#include <QApplication>
#include <QPainter>
#include <QtGui>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     QString init_worldmap = ":/images/world_images/maze2.png";
     MainWindow w = MainWindow(NULL,init_worldmap);
     World test;
     test.createWorld(init_worldmap, 5,5,0.25);
     //scene->addItem(test);

     std::cout << "Columns:" << test.getCols() << "Rows:" << test.getRows() << std::endl;
     std::cout << "health:" << test.getProtagonist()->getHealth() << "x:" << test.getProtagonist()->getXPos() << "y:" << test.getProtagonist()->getYPos() << std::endl;
     w.show();
    return a.exec();


}
