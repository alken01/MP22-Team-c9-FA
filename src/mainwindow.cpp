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
    initControllers();

    setupUIComponents();
    setupConnections();
    filterCommands();
    ui->comboBox->setCurrentIndex(0);
    initViews();
}

void MainWindow::setupWorlds() {
    std::cout << "MainWindow setupWorlds" << std::endl;

    
    QString mapPath = ":/resources/world_images/";

    // create Map objects
    for (auto mapName : mapNameList) {
        Map map(QString(mapPath + mapName + ".png"), mapName);
        mapList.push_back(map);
        std::cout << "MainWindow creating map " << map.getPath().toStdString()
                  << std::endl;
    }

    // create WorldModel objects

    unsigned int XENEMY_NR = 15;  // change this
    for (Map map : mapList) {
        std::cout << "MainWindow creating world " << map.getName().toStdString()
                  << std::endl;
        auto worldModel = std::make_shared<WorldModel>(map, XENEMY_NR);
        worldList[map.getName()] = worldModel;
    }

    // Access an activeWorld using a specific key from mapList
    QString keyToFind = mapList[0].getName();
    if (worldList.find(keyToFind) != worldList.end()) {
        activeWorld = worldList[keyToFind];
        std::cout << "MainWindow activeWorld is " << keyToFind.toStdString()
                  << std::endl;
    } else {
        // Handle the case where the key is not found
        std::cout << "Key not found" << std::endl;
    }
}

void MainWindow::initControllers() {
    std::cout << "MainWindow initControllers" << std::endl;
    controller = std::make_shared<Controller>(activeWorld);
    viewController = std::make_shared<ViewController>(activeWorld);
    // aiController = std::make_shared<AIController>(controller);
}

void MainWindow::setupUIComponents() {
    ui->setupUi(this);

    textInput = ui->lineEdit;
    ui->textEdit_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    health = ui->progressBar;
    health->setRange(0, 100);
    health->setValue(activeWorld->getProtagonist()->getHealth());

    energy = ui->progressBar_2;
    energy->setRange(0, 100);
    energy->setValue(activeWorld->getProtagonist()->getEnergy());

    completer = new QCompleter(CommandsMap::getCommands(), this);
    ui->lineEdit->setCompleter(completer);

    ui->comboBox->addItems(mapNameList);

    viewStatus = TEXT_VIEW;
    changeScene();
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
    viewController->getQGraphicsView().get()->hide();
    viewController->drawWorlds();
}

void MainWindow::changeScene() {
    // true if text view is active
    const bool isTextView = (viewStatus == TEXT_VIEW);

    // hide text view and show graphics view
    viewController->getQTextView().get()->setVisible(isTextView);
    viewController->getQGraphicsView().get()->setVisible(!isTextView);

    // change these elements
    ui->zoomSlider->setVisible(!isTextView);   // hide zoom slider
    ui->lineEdit->setVisible(isTextView);      // hide line edit
    ui->textEdit_11->setVisible(!isTextView);  // show text edit
    ui->textEdit_4->clear();                   // clear terminal

    viewStatus = isTextView ? GRAPHICS_VIEW : TEXT_VIEW;  // flip view status
}

void MainWindow::pressEntered() {
    if (isGameOver()) return;
    QString input = textInput->text();
    std::cout << "MainWindow pressEntered" << std::endl;
    controller->handleInput(input);
    // viewController->movePlayer?? or in controller
    viewController->updateViews();

    if (input == HELP_COMMAND) {
        printHelpCommands();
    } else if (!input.isNull() || input.left(4) == "goto") {
        printTerminal(input);

    } else {
        printTerminal(UNRECOGNIZED_INPUT_MESSAGE);
    }
    textInput->clear();
    getFeedback();
    updateVitals();
}

void MainWindow::textEntered() {
    QString input = textInput->text().trimmed();
    if (input.length() < 1) return;
    for (const QString& command : filteredCommands) {
        // if the command starts with the input, autocomplete
        if (command.startsWith(input)) {
            textInput->setText(command);
            pressEntered();
        }
    }
}

bool MainWindow::isGameOver() {
    bool isPlayerDead = !activeWorld->isProtagonistAlive();

    if (isPlayerDead) {
        // QString message = isGameWon ? WIN_MESSAGE : LOSE_MESSAGE;
        // printTerminal(message);
        showRestartButton(true);
        return true;
    }
    return false;
}

void MainWindow::filterCommands() {
    for (const QString& command : CommandsMap::getCommands())
        if (!command.startsWith("goto")) filteredCommands.append(command);
}

void MainWindow::mapChanged() {
    auto newMap = ui->comboBox->currentText();
    std::cout << "MainWindow mapChanged" << std::endl;
    // active world should point to the new map
    // activeWorld = worldList[newMap];
    QString keyToFind = newMap;
    if (worldList.find(keyToFind) != worldList.end()) {
        activeWorld = worldList[keyToFind];
        std::cout << "MainWindow activeWorld is " << keyToFind.toStdString()
                  << std::endl;
    } else {
        // Handle the case where the key is not found
        std::cout << "Key not found" << std::endl;
        return;
    }
    controller->setWorld(activeWorld);
    viewController->setWorld(activeWorld);
    
    viewController->changeMap();
    // controller->changeMap(newMap);
    // viewController->updateViews();

    updateVitals();
    ui->textEdit_4->clear();
    showRestartButton(false);

    // empty line edit after autocomplete
    QObject::connect(completer, SIGNAL(activated(const QString&)), ui->lineEdit,
                     SLOT(clear()), Qt::QueuedConnection);
}

void MainWindow::updateVitals() {
    health->setValue(activeWorld->getProtagonist()->getHealth());
    energy->setValue(activeWorld->getProtagonist()->getEnergy());
    // ui->lcdNumber->display(controller->getPoisoned());
}

void MainWindow::printHelpCommands() {
    printTerminal(HELP_MESSAGE_TITLE);
    for (QString command : CommandsMap::getCommands()) {
        printTerminal(command);
    }
    printTerminal(HELP_MESSAGE_FOOTER);
}

void MainWindow::showRestartButton(bool show) {
    ui->pushButton->setVisible(!show);
    ui->pushButton_2->setVisible(show);
}

void MainWindow::printTerminal(QString message) {
    ui->textEdit_4->append(message);
}

void MainWindow::getFeedback() {
    // auto message = controller->getTerminalOut();
    // if (message.isNull()) return;
    // printTerminal(message);
    // controller->setTerminalOut(NULL);
}

void MainWindow::setHeuristic() {
    // aiController->setWhiteValue(ui->heuristicSlider->value() / 10);
}

void MainWindow::autoplay() {
    // aiController->autoPlay();
}

void MainWindow::changeSpeed() {
    viewController->setAnimationSpeed(ui->animationSlider->value() * 10);
}
