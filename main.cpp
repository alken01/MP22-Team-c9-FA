#include "QtWidgets/qgraphicsscene.h"
#include "QtWidgets/qgraphicsview.h"
#include "mainwindow.h"
#include "world.h"
#include "controller.h"
#include "graphicalview.h"
#include "textview.h"
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



    w.show();
    return a.exec();


}
