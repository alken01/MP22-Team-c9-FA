#include "game_controller.h"

GameController::GameController()
    : graphical_view(std::make_shared<GraphicalView>()),
      text_view(std::make_shared<TextView>()),
      Qtext_view(std::make_shared<QGraphicsView>()),
      Qgraphics_view(std::make_shared<QGraphicsView>()),
      animationSpeed(500) {
    // commandController = std::make_unique<CommandController>(this);
    // mapController = std::make_unique<MapController>(this);
    // movementController = std::make_unique<MovementController>(this);
    // pathfindingController = std::make_unique<PathfindingController>(this);
    textView = std::make_unique<TextView>(this);
    graphicalView = std::make_unique<GraphicalView>(this);

    initWorlds();
}

void GameController::initWorlds() {
    QString init_worldmap = getMapPath(mapList[0]);
    newMap = std::make_shared<World>();
    QPixmap file(init_worldmap);
    int height = file.height();
    newMap->createWorld(init_worldmap, height / 2, height / 2, 0.25);
    world = std::make_shared<WorldModel>(newMap, height / 2);
}

void GameController::handleInput(QString input) {
    // Call the appropriate controller based on the input
    if (input == "switch view")
    {
        switchViews();
    }
    else
    {
        commandController->handleInput(input);
    }
}

void GameController::restart() {
    // Implement the logic to reset the game and restart from the initial state.
}

void GameController::switchToGraphic() {
    // Implement the logic to switch to graphical view.
    graphicalView->show();  // Show the graphical view window
}

void GameController::switchToText() {
    // Implement the logic to switch to text-based view.
    textView->show();  // Show the text-based view window
}

void GameController::switchViews() {
    // Implement the logic to toggle between graphical and text-based views.
    if (graphicalView->isVisible())
    {
        graphicalView->hide();
        textView->show();
    }
    else
    {
        textView->hide();
        graphicalView->show();
    }
}
