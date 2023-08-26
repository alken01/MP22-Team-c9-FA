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

MainWindow::MainWindow(QWidget* parent, std::shared_ptr<Controller> controller,
                       std::shared_ptr<ViewController> viewController)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->controller = controller;
    this->viewController = viewController;

    std::cout << "MainWindow constructor" << std::endl;

    ui->setupUi(this);
    std::cout << "MainWindow setupUi" << std::endl;
    setupUIComponents();
    std::cout << "MainWindow setupUIComponents" << std::endl;
    setupConnections();
    std::cout << "MainWindow setupConnections" << std::endl;
    filterCommands();
    std::cout << "MainWindow filterCommands" << std::endl;
    ui->comboBox->setCurrentIndex(0);
    std::cout << "MainWindow constructor end" << std::endl;
    initViews();
    std::cout << "MainWindow initViews" << std::endl;
}

void MainWindow::setupUIComponents() {
    textInput = ui->lineEdit;
    ui->textEdit_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    health = ui->progressBar;
    health->setRange(0, 100);
    health->setValue(controller->getWorld()->getProtagonist()->getHealth());

    energy = ui->progressBar_2;
    energy->setRange(0, 100);
    energy->setValue(controller->getWorld()->getProtagonist()->getEnergy());

    completer = new QCompleter(CommandsMap::getCommands(), this);
    ui->lineEdit->setCompleter(completer);

    ui->comboBox->addItems(controller->getMapList());

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
    controller->commandReceived(input);
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
    bool isPlayerDead = !controller->isProtagonistAlive();

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
    viewController->changeMap(ui->comboBox->currentText());

    updateVitals();
    ui->textEdit_4->clear();
    showRestartButton(false);

    // empty line edit after autocomplete
    QObject::connect(completer, SIGNAL(activated(const QString&)), ui->lineEdit,
                     SLOT(clear()), Qt::QueuedConnection);
}

void MainWindow::updateVitals() {
    health->setValue(controller->getWorld()->getProtagonist()->getHealth());
    energy->setValue(controller->getWorld()->getProtagonist()->getEnergy());
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
