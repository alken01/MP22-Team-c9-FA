#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QString>
#include <QtWidgets>
#include <iostream>
#include <memory>
#include "aicontroller.h"
#include "controller.h"
#include "map.h"
#include "viewcontroller.h"
#include "worldmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent);
        void changeScene();
        void goToPath(int x, int y);
        void updatePath(QString input);
        void pressEntered();
        std::vector<QString> pathToText(std::vector<std::pair<int, int>> path);

    private:
        // UI ELEMENTS
        Ui::MainWindow* ui;
        QLineEdit* commandTerminalInput;
        QTextEdit* terminalHistory;
        QGraphicsView textView;
        QProgressBar *healthBar, *energyBar;
        QCompleter* completer;
        QComboBox* mapBoxList;
        bool viewStatus;

        std::shared_ptr<Controller> controller;
        std::shared_ptr<ViewController> viewController;
        QStringList filteredCommands;

        void activateNewWorld(QString mapName);
        unsigned int XENEMY_NR = 10;  

        QString mapPath = ":/resources/world_images/";
        QStringList mapNameList = {"maze1", "maze2", "maze3", "worldmap",
                                   "worldmap4"};
        std::vector<Map> mapList;
        std::unordered_map<QString, std::shared_ptr<WorldModel>> worldList;
        std::shared_ptr<WorldModel> activeWorld;

        void setupWorlds();
        void initControllers();
        void initViews();
        void setupUIComponents();
        void setupConnections();
        void updateVitals();
        void printHelpCommands();
        bool isGameOver();
        void showRestartButton(bool show);
        void textEntered();
        void filterCommands();
        void mapChanged();
        void setHeuristic();
        void autoplay();
        void changeSpeed();
        void printTerminal(QString message);
};
#endif  // MAINWINDOW_H
