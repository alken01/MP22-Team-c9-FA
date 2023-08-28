#include "textview.h"

#ifdef __APPLE__
QFont TEXT_FONT("SF Mono");
#else
QFont TEXT_FONT("Monospace");
#endif

TextView::TextView() {
    textScene = new QGraphicsScene();
}

void TextView::draw(std::shared_ptr<WorldModel> worldModel,
                    std::shared_ptr<QGraphicsView> textView) {
    this->worldModel = worldModel;
    outputView = textView;
    initializeMap();
    populateWorldMap();
    updateVisibleMap();
    combineLinesToString();
    updateText();
    textView->setScene(textScene);
}
void TextView::setupTimers() {
    poisonedEffectTimer.setInterval(Constants::TIMER_ANIMATION * 2);
    healthFightTimer.isSingleShot();
    healthFightTimer.setInterval(Constants::TIMER_ANIMATION);
    connect(&poisonedEffectTimer, &QTimer::timeout, this,
            &TextView::setPoisoned);
    connect(&healthFightTimer, &QTimer::timeout, this,
            &TextView::resetBackgroundColor);
}

void TextView::initializeMap() {
    // make vectorMap the size of the world and fill it with empty spaces
    vectorMap.clear();
    vectorMap.resize(worldModel->getHeight());
    for (int i = 0; i < worldModel->getHeight(); i++) {
        vectorMap[i].resize(worldModel->getWidth());
        vectorMap[i].fill(Constants::EMPTY_SYMBOL);
    }
}

void TextView::populateWorldMap() {
    populateTiles();
    populateEnemies();
    populateHealthPacks();
    populateProtagonist();
}

void TextView::populateTiles() {
    for (const std::shared_ptr<Tile>& tile : worldModel->getTiles()) {
        QChar symbol = Constants::grayscaleToASCII(tile->getValue());
        changeSignAtCoord(tile->getCoordinates(), symbol);
    }
}

void TextView::populateEnemies() {
    for (const auto& enemyPair : worldModel->getEnemies()) {
        const std::shared_ptr<Enemy>& enemy = enemyPair.second;
        Coordinates coord = enemy->getCoordinates();
        QChar symbol = Constants::getSymbol(enemy->getTileType());
        changeSignAtCoord(coord, symbol);
    }
}

void TextView::populateHealthPacks() {
    for (const auto& healthPackPair : worldModel->getHealthPacks()) {
        const std::shared_ptr<Tile>& healthPack = healthPackPair.second;
        changeSignAtCoord(healthPack->getCoordinates(),
                          Constants::HEALTHPACK_SYMBOL);
    }
}

void TextView::populateProtagonist() {
    Coordinates coord = worldModel->getProtagonist()->getCoordinates();
    changeSignAtCoord(coord, Constants::PROTAGONIST_SYMBOL);
}

void TextView::combineLinesToString() {
    combinedMap = std::make_shared<QString>();
    for (const auto& line : visibleVectorMap) {
        combinedMap->append(line);
    }
}

void TextView::renderMap() {
    updateView();
    updateVisibleMap();
    combineLinesToString();
    updateText();
}

void TextView::updateVisibleMap() {
    Coordinates protCoord = worldModel->getProtagonist()->getCoordinates();

    // Calculate the top position of the view (number of rows to skip)
    int viewTop = protCoord.getY() - Constants::Y_OFFSET + 1;
    int rowSkip = (viewTop > 0) ? 0 : viewTop;

    // Extract the relevant portion of the world map based on the viewTop position
    QVector<QString> tempMap =
    vectorMap.mid(viewTop, Constants::TOTAL_ROWS - rowSkip);

    // Calculate the left position of the view (number of columns to skip)
    int viewLeft = protCoord.getX() - Constants::X_OFFSET + 1;
    int colSkip = (viewLeft > 0) ? 0 : viewLeft;

    // Adjust each line in the tempMap to show the visible portion of the world map
    for (int i = 0; i < tempMap.size(); i++) {
        tempMap[i] =
        tempMap[i].mid(viewLeft, Constants::TOTAL_COLUMNS - colSkip) + "\n";
    }
    visibleVectorMap = tempMap;
}

void TextView::changeSignAtCoord(Coordinates coord, QChar input) {
    vectorMap[coord.getY()][coord.getX()] = input;
}

void TextView::protagonistDies() {
    Coordinates coord = worldModel->getProtagonist()->getCoordinates();
    changeSignAtCoord(coord, Constants::DEAD_SYMBOL);
    updateVisibleMap();
    // updateText();
    updateView();
}

void TextView::setHealed() {
    setTextViewState(Constants::HEALED_COLOR);
    healthFightTimer.start();
}

void TextView::setFighting() {
    setTextViewState(Constants::FIGHTING_COLOR);
    healthFightTimer.start();
}

void TextView::setPoisoned() {
    setTextViewState(Constants::POISONED_COLOR);
    poisonedEffectTimer.start();
}

void TextView::setTextViewState(const QColor& color) {
    textScene->setBackgroundBrush(color);
}

void TextView::updateText() {
    textScene->clear();
    textScene->addText(*combinedMap, TEXT_FONT);
}

void TextView::updateView() {
    outputView->scene()->update();
}

void TextView::resetBackgroundColor() {
    textScene->setBackgroundBrush(Qt::transparent);
}

void TextView::startTimer() {
    poisonedEffectTimer.start();
}

void TextView::stopTimer() {
    poisonedEffectTimer.stop();
    resetBackgroundColor();
}