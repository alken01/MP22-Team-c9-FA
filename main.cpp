#include "mainwindow.h"
#include "world.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

     QString init_worldmap = ":/images/world_images/maze2.png";

     World test;
     test.createWorld(init_worldmap, 5,5,0.25);
     std::cout << "Columns:" << test.getCols() << "Rows:" << test.getRows() << std::endl;

    w.show();
    return a.exec();


}
