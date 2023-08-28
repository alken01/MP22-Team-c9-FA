#include "mainwindow.h"
#include <iostream>
#include "ui_mainwindow.h"

const int TEXT_VIEW = true;
const int GRAPHICS_VIEW = false;

const QString WIN_MESSAGE = "Congratulations! You won!";
const QString LOSE_MESSAGE = "Your journey ends here. Press restart.";
const QString HELP_MESSAGE_TITLE = "Need guidance? Available commands:";
const QString HELP_MESSAGE_FOOTER = "Type any command to continue.";
const QString HELP_COMMAND = "help";
const QString UNRECOGNIZED_INPUT_MESSAGE =
"Invalid command. Type '" + HELP_COMMAND + "' for options.";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setupWorlds();
    setupUIComponents();
    setupConnections();
    filterCommands();
    initControllers();
    initViews();
}

void MainWindow::setupWorlds() {
    for (auto mapName : mapNameList) {
        mapList.push_back(Map(QString(mapPath + mapName + ".png"), mapName));
    }
    for (Map map : mapList) {
        worldList[map.getName()] = std::make_shared<WorldModel>(map, XENEMY_NR);
    }
    activateNewWorld(mapNameList[0]);
}

void MainWindow::activateNewWorld(QString mapName) {
    if (worldList.find(mapName) != worldList.end()) {
        activeWorld = worldList[mapName];
    } else {
        std::cout << "Map not found" << std::endl;
    }
}

void MainWindow::initControllers() {
    controller = std::make_shared<Controller>(activeWorld);
    viewController = std::make_shared<ViewController>(activeWorld);
    aiController = std::make_shared<AIController>(activeWorld);
}

void MainWindow::setupUIComponents() {
    ui->setupUi(this);
    // set up commandTerminalInput
    commandTerminalInput = ui->lineEdit;

    // set up command history
    terminalHistory = ui->textEdit_4;
    terminalHistory->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set up health bar
    healthBar = ui->progressBar;
    healthBar->setRange(0, 100);
    healthBar->setValue(activeWorld->getProtagonist()->getHealth());

    // set up energy bar
    energyBar = ui->progressBar_2;
    energyBar->setRange(0, 100);
    energyBar->setValue(activeWorld->getProtagonist()->getEnergy());

    // set up autocompleter
    completer = new QCompleter(CommandsMap::getCommands(), this);
    ui->lineEdit->setCompleter(completer);

    // set up map list
    mapBoxList = ui->comboBox;
    mapBoxList->addItems(mapNameList);
    mapBoxList->setCurrentIndex(0);

    // change map and restart buttons
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);

    viewStatus = TEXT_VIEW;
}

// Set up the signal-slot connections
void MainWindow::setupConnections() {
    connect(ui->pushButton, &QPushButton::clicked, this,
            &MainWindow::changeScene);
    connect(ui->lineEdit, &QLineEdit::textChanged, this,
            &MainWindow::textEntered);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this,
            &MainWindow::pressEntered);
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this,
            &MainWindow::mapChanged);
    connect(ui->heuristicSlider, &QSlider::sliderMoved, this,
            &MainWindow::setHeuristic);
    connect(ui->pushButton_3, &QPushButton::clicked, this,
            &MainWindow::autoplay);
    connect(ui->pushButton_2, &QPushButton::clicked, this,
            &MainWindow::mapChanged);
    connect(ui->animationSlider, &QSlider::sliderMoved, this,
            &MainWindow::changeSpeed);

    QObject::connect(completer, SIGNAL(activated(const QString&)), ui->lineEdit,
                     SLOT(clear()), Qt::QueuedConnection);
}

void MainWindow::initViews() {
    ui->verticalLayout_2->addWidget(viewController->getQTextView().get());
    ui->verticalLayout_2->addWidget(viewController->getQGraphicsView().get());

    viewController->drawWorlds();
}

void MainWindow::changeScene() {
    // true if text view is active
    const bool isTextView = (viewStatus == TEXT_VIEW);

    // hide text view and show graphics view
    viewController->switchViews();

    // change these elements
    ui->zoomSlider->setVisible(!isTextView);   // hide zoom slider
    ui->lineEdit->setVisible(isTextView);      // hide line edit
    ui->textEdit_11->setVisible(!isTextView);  // show text edit
    terminalHistory->clear();                  // clear terminal

    viewStatus = isTextView ? GRAPHICS_VIEW : TEXT_VIEW;  // flip view status
}

void MainWindow::pressEntered() {
    if (isGameOver()) return;

    QString input = commandTerminalInput->text();
    int moveResult = Controller::MOVE;
    if (input.size() >= 4 && input.left(4) == "goto") {
        std::vector<QString> path = aiController->gotoHelper(input);
        if (path.size() > 0) {
            for (QString coord : path) {
                controller->handleInput(coord);
                viewController->render();
                // wait for animation to finish
                QEventLoop loop;
                QTimer::singleShot(aiController->getAnimation(), &loop, SLOT(quit()));
                loop.exec();
            }
        }
        
    } else {
        moveResult = controller->handleInput(input);
    }

    viewController->render();
    if (moveResult == Controller::POISON) {
        viewController->poisoned();
    }
    if (moveResult == Controller::DIE) {
        viewController->dead();
    }
    if (moveResult == Controller::HEAL) {
        viewController->healed();
    }
    if (moveResult == Controller::XFIGHT || moveResult == Controller::FIGHT) {
        viewController->fighting();
    }

    if (input == HELP_COMMAND) {
        printHelpCommands();
    } else if (!input.isNull() || input.left(4) == "goto") {
        printTerminal(input);
    } else {
        printTerminal(UNRECOGNIZED_INPUT_MESSAGE);
    }
    commandTerminalInput->clear();
    updateVitals();
}

void MainWindow::textEntered() {
    // check if autocomplete
    QString input = commandTerminalInput->text().trimmed().toLower();
    if (input.length() < 1) return;
    for (const QString& command : filteredCommands) {
        // if the command starts with the input, autocomplete
        if (command.startsWith(input)) {
            commandTerminalInput->setText(command);
            pressEntered();
        }
    }
}

bool MainWindow::isGameOver() {
    bool isPlayerDead = !activeWorld->isProtagonistAlive();
    bool isGameWon = activeWorld->isGameWon();
    if (isPlayerDead || isGameWon) {
        QString message = isGameWon ? WIN_MESSAGE : LOSE_MESSAGE;
        printTerminal(message);
        return true;
    }
    return false;
}

void MainWindow::filterCommands() {
    for (const QString& command : CommandsMap::getCommands())
        if (!command.startsWith("goto")) filteredCommands.append(command);
}

void MainWindow::mapChanged() {
    auto newMap = mapBoxList->currentText();
    activateNewWorld(newMap);

    controller->setWorld(activeWorld);
    viewController->setWorld(activeWorld);
    aiController->setWorld(activeWorld);

    viewController->drawWorlds();

    updateVitals();
    terminalHistory->clear();
    QObject::connect(completer, SIGNAL(activated(const QString&)), ui->lineEdit,
                     SLOT(clear()), Qt::QueuedConnection);
}

void MainWindow::updateVitals() {
    healthBar->setValue(activeWorld->getProtagonist()->getHealth());
    energyBar->setValue(activeWorld->getProtagonist()->getEnergy());
    ui->lcdNumber->display(activeWorld->getProtagonist()->getPoison());
}

void MainWindow::printHelpCommands() {
    printTerminal(HELP_MESSAGE_TITLE);
    for (QString command : CommandsMap::getCommands()) {
        printTerminal(command);
    }
    printTerminal(HELP_MESSAGE_FOOTER);
}

void MainWindow::printTerminal(QString message) {
    terminalHistory->append(message.trimmed().toLower());
}

void MainWindow::setHeuristic() {
    aiController->setWhiteValue(ui->heuristicSlider->value() / 10);
}

void MainWindow::autoplay() {
    aiController->autoPlay();
}

void MainWindow::changeSpeed() {
    aiController->setAnimationSpeed(ui->animationSlider->value() * 10);
}
