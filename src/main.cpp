#include <QApplication>
#include <memory>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    try {
        QApplication app(argc, argv);
        std::shared_ptr<Controller> controller = std::make_shared<Controller>();
        std::shared_ptr<ViewController> viewController =
        std::make_shared<ViewController>(controller);
        MainWindow* window =
        new MainWindow(nullptr, controller, viewController);
        window->show();
        int exitCode = app.exec();
        return exitCode;
    } catch (const std::exception& e) {
        qDebug() << "An exception occurred: " << e.what();
        return -1;
    }
}
