#include <QApplication>
#include <memory>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow* window = new MainWindow(nullptr);
    window->show();
    int exitCode = app.exec();
    return exitCode;
}
