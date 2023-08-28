#include "textview.h"

#ifdef __APPLE__
QFont TEXT_FONT("SF Mono");
#else
QFont TEXT_FONT("Monospace");
#endif

const QColor POISONED_COLOR = QColor("purple");
const QColor HEALED_COLOR = QColor("green");
const QColor FIGHTING_COLOR = QColor("orange");
const int TIMER_ANIMATION = 1000;

const QChar WALL_SYMBOL = QChar(0x2588);     // █
const QChar DARKEST_SYMBOL = QChar(0x2593);  // ▓
const QChar DARKER_SYMBOL = QChar(0x2592);   // ▒
const QChar DARK_SYMBOL = QChar(0x2591);     // ░
const QChar EMPTY_SYMBOL = QChar(' ');       // _

const QChar PROTAGONIST_SYMBOL = QChar(0x263A);  // ☺
const QChar HEALTHPACK_SYMBOL = QChar(0x2665);   // ♥
const QChar ENEMY_SYMBOL = QChar(0x263B);        // ☻
const QChar PENEMY_SYMBOL = QChar(0x263C);       // ☼
const QChar XENEMY_SYMBOL = QChar(0x263D);       // ☽
const QChar DEAD_SYMBOL = QChar(0x2620);         // ☠

const int TOTAL_ROWS = 18;
const int TOTAL_COLUMNS = 60;
const int Y_OFFSET = 5;
const int X_OFFSET = 7;

TextView::TextView() {
    std::cout << "Creating text view" << std::endl;
    healthFightTimer.isSingleShot();
    textScene = new QGraphicsScene();
}

void TextView::draw(std::shared_ptr<WorldModel> worldModel,
                    std::shared_ptr<QGraphicsView> textView) {
    std::cout << "Drawing text view" << std::endl;
    this->worldModel = worldModel;
    outputView = textView;
    textScene->clear();
    textScene->setBackgroundBrush(Qt::transparent);

    setupTimers();
    initializeMap();

    populateWorldMap();
    updateVisibleMap();
    combineLinesToString();

    updateText();
    textView->setScene(textScene);
}

void TextView::setupTimers() {
    poisonedEffectTimer.setInterval(TIMER_ANIMATION * 2);
    healthFightTimer.setInterval(TIMER_ANIMATION);
    connect(&poisonedEffectTimer, &QTimer::timeout, this,
            &TextView::setPoisoned);
    connect(&healthFightTimer, &QTimer::timeout, this,
            &TextView::resetBackgroundColor);
}

void TextView::initializeMap() {
    vectorMap = QVector<QString>(worldModel->getHeight() + 1);
    for (int i = 0; i < worldModel->getWidth(); ++i) {
        vectorMap[i] = QString(worldModel->getWidth(), EMPTY_SYMBOL);
    }
}

void TextView::populateWorldMap() {
    for (const std::shared_ptr<Tile>& tile : worldModel->getTiles()) {
        Coordinates coord = tile->getCoordinates();
        changeSignAtCoord(coord, grayscaleToASCII(tile->getValue()));
    }

    for (const auto& enemyPair : worldModel->getEnemies()) {
        const std::shared_ptr<Enemy>& enemy = enemyPair.second;
        Coordinates coord = enemy->getCoordinates();
        Tile::Type enemyType = enemy->getTileType();
        if (enemyType == Tile::Enemy) {
            changeSignAtCoord(coord, ENEMY_SYMBOL);
        } else if (enemyType == Tile::PEnemy) {
            changeSignAtCoord(coord, PENEMY_SYMBOL);
        } else if (enemyType == Tile::XEnemy) {
            changeSignAtCoord(coord, XENEMY_SYMBOL);
        }
    }

    for (const auto& healthPackPair : worldModel->getHealthPacks()) {
        const std::shared_ptr<Tile>& healthPack = healthPackPair.second;
        changeSignAtCoord(healthPack->getCoordinates(), HEALTHPACK_SYMBOL);
    }

    Coordinates coord = worldModel->getProtagonist()->getCoordinates();
    changeSignAtCoord(coord, PROTAGONIST_SYMBOL);
}

void TextView::combineLinesToString() {
    combinedMap = std::make_shared<QString>();
    for (const auto& line : visibleVectorMap) {
        combinedMap->append(line);
    }
}

// This code will be used in controller / changed so it gets input from
// controller
void TextView::moveProtagonist() {
    std::cout << "Moving protagonist" << std::endl;
    Coordinates protCoord = worldModel->getProtagonist()->getCoordinates();

    // check for all 6 pos around protagonist
    for (int x = std::max(0, protCoord.getX() - 1);
         x <= std::min(worldModel->getWidth() - 1, protCoord.getX() + 1); x++) {
        for (int y = std::max(0, protCoord.getY() - 1);
             y <= std::min(worldModel->getHeight() - 1, protCoord.getY() + 1);
             y++) {
            Coordinates coord = Coordinates(x, y);
            int worldPos = x + y * worldModel->getWidth();
            float tileValue = worldModel->getTiles().at(worldPos)->getValue();
            changeSignAtCoord(coord, grayscaleToASCII(tileValue));
        }
    }
    changeSignAtCoord(protCoord, QChar(PROTAGONIST_SYMBOL));
    
    updateVisibleMap();
    combineLinesToString();
    updateText();
}

void TextView::updateVisibleMap() {
    std::cout << "Updating visible map" << std::endl;
    Coordinates protCoord = worldModel->getProtagonist()->getCoordinates();

    // Calculate the top position of the view (number of rows to skip)
    int viewTop = protCoord.getY() - Y_OFFSET + 1;
    int rowSkip = (viewTop > 0) ? 0 : viewTop;

    // Extract the relevant portion of the world map based on the viewTop position
    QVector<QString> tempMap = vectorMap.mid(viewTop, TOTAL_ROWS - rowSkip);

    // Calculate the left position of the view (number of columns to skip)
    int viewLeft = protCoord.getX() - X_OFFSET + 1;
    int colSkip = (viewLeft > 0) ? 0 : viewLeft;

    // Adjust each line in the tempMap to show the visible portion of the world map
    for (int i = 0; i < tempMap.size(); i++) {
        tempMap[i] = tempMap[i].mid(viewLeft, TOTAL_COLUMNS - colSkip) + "\n";
    }
    visibleVectorMap = tempMap;
}

void TextView::changeSignAtCoord(Coordinates coord, QChar input) {
    vectorMap[coord.getY()][coord.getX()] = input;
}

QChar TextView::grayscaleToASCII(float intensity) {
    if (intensity == INFINITY) return WALL_SYMBOL;
    if (intensity > 1) return HEALTHPACK_SYMBOL;
    if (intensity < 0.2) return DARKEST_SYMBOL;
    if (intensity < 0.5) return DARKER_SYMBOL;
    if (intensity < 0.8) return DARK_SYMBOL;
    return EMPTY_SYMBOL;
}

void TextView::protagonistDies() {
    Coordinates coord = worldModel->getProtagonist()->getCoordinates();
    changeSignAtCoord(coord, DEAD_SYMBOL);
    updateVisibleMap();
    // updateText();
    updateView();
}

void TextView::setHealed() {
    setTextViewState(HEALED_COLOR);
    healthFightTimer.start();
}

void TextView::setFighting() {
    setTextViewState(FIGHTING_COLOR);
    healthFightTimer.start();
}

void TextView::setPoisoned() {
    setTextViewState(POISONED_COLOR);
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
    moveProtagonist();
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