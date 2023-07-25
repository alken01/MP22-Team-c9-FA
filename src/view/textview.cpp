#include "textview.h"

#include <iostream>

#include "world.h"

#ifdef __APPLE__
QFont choose_font("SF Mono");
#else
QFont choose_font("Monospace");
#endif

TextView::TextView() {
    // animation timers
    timer2.isSingleShot();
    textscene = new QGraphicsScene();
}

void TextView::draw(shared_ptr<WorldModel> w,
                    shared_ptr<QGraphicsView> textView) {
    world = w;
    height = w->getHeight();
    width = w->getWidth();
    auto enemies = w->getEnemies();
    auto healthPacks = w->getHealthPacks();
    auto protagonist = w->getProtagonist();
    auto tiles = w->getTiles();

    outputView = textView;

    startposX = w->getProtagonist()->getXPos();
    startposY = w->getProtagonist()->getYPos();

    textscene->clear();
    textscene->setBackgroundBrush(Qt::transparent);

    // timers for animations
    timer.setInterval(2000);
    timer2.setInterval(1000);

    // poison timer
    connect(&timer, &QTimer::timeout, this, &TextView::activatePoisoned);

    // health timer + fighting
    connect(&timer2, &QTimer::timeout, this, &TextView::resetBg);

    qVec.clear();

    // Qstring = stores a string of 16-bit QChars
    auto wi = QString("+");  // Create Qstring for width
    auto h = QString("|");   // Create Qstring for height

    // for each column +---+ x width
    for (int i = 0; i < width; i++) {
        wi.append("---+");
    }
    // for each column |   | x width
    for (int i = 0; i < width; i++) {
        h.append("   |");
    }

    // for each row repeat shape x height
    for (int q = 0; q < height; q++) {
        qVec.push_back(wi);
        // qVec.append("\n");
        qVec.push_back(h);
        // qVec.append("\n");
    }

    // close map bottom line
    qVec.push_back(wi);
    // add walls
    for (unsigned long i = 0; i < tiles.size(); ++i) {
        int x = tiles.at(i)->getXPos();
        int y = tiles.at(i)->getYPos();
        changeSignAtCoord(x, y, grayscaleToASCII(tiles.at(i)->getValue()));
    }

    // add enemies
    for (unsigned long i = 0; i < enemies.size(); ++i) {
        unsigned long x = enemies.at(i)->getXPos();
        unsigned long y = enemies.at(i)->getYPos();

        auto temp = dynamic_pointer_cast<PEnemy>(enemies.at(i));

        if (temp != nullptr) {
            changeSignAtCoord(x, y, 'P');
            cout.flush();
            cout << "P enemy at Y:" << y << "X:" << x << endl;
        } else {
            auto temp2 = dynamic_pointer_cast<XEnemy>(enemies.at(i));

            if (temp2 != nullptr) {
                changeSignAtCoord(x, y, 'X');
                cout.flush();
                cout << "X enemy at Y:" << y << "X:" << x << "added" << endl;
            } else {
                changeSignAtCoord(x, y, 'E');
                cout << "Normal enemy at Y:" << y << "X:" << x << "added"
                     << endl;
            }
        }
    }

    // add health
    for (unsigned long i = 0; i < healthPacks.size(); ++i) {
        int x = healthPacks.at(i)->getXPos();
        int y = healthPacks.at(i)->getYPos();
        changeSignAtCoord(x, y, 'H');
        cout.flush();
        cout << "Health added at Y:" << y << "X:" << x << endl;
    }

    // add prot
    unsigned long x = protagonist->getXPos();
    unsigned long y = protagonist->getYPos();
    changeSignAtCoord(x, y, '$');

    // cut world to size
    moveCamera();

    // couldn't make newline characters work when printing text seperately -->
    // combine all first into single string
    stringWorld = make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }

    textscene->addText(*stringWorld, choose_font);
    textView->setScene(textscene);
}

// add special characters to show greyscale
QChar TextView::grayscaleToASCII(float intensity) {
    if (intensity == INFINITY)
        return QChar('@');
    if (intensity > 0.5)
        return QChar(' ');

    vector<char> characters = {'.', ':', '-', '=', '+', '*', '#', '%'};
    // scale the intensity value to the range of the character set and round it
    // to the nearest index cout<< "intesity"<<intensity<<endl;
    int index = round((intensity + 0.49) * (characters.size() - 1));

    return QChar(characters[characters.size() - index - 1]);
}

// This code will be used in controller / changed so it gets input from
// controller
void TextView::movProtagonist(int x1, int y1, int x2, int y2,
                              shared_ptr<WorldModel> w) {
    int i = y1 * w->getWidth() + x1;
    auto tiles = w->getTiles();
    changeSignAtCoord(x1, y1, grayscaleToASCII(tiles.at(i)->getValue()));
    changeSignAtCoord(x2, y2, '$');
    moveCamera();

    stringWorld = make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }

    textscene->clear();
    textscene->addText(*stringWorld, choose_font);
}

void TextView::changeSignAtCoord(unsigned long x, unsigned long y,
                                 QChar input) {
    qVec[y * 2 + 1].replace(2 + x * 4, 1, input);
    // cut view
    moveCamera();

    // update display
    stringWorld = make_shared<QString>();
    for (int i = 0; i < qVecPlayer.size(); ++i) {
        stringWorld->append(qVecPlayer.at(i));
    }
}

void TextView::updateView() {
    outputView->scene()->update();
}

void TextView::protDead(int x, int y) {
    changeSignAtCoord(x, y, 'D');
    textscene->clear();
    textscene->addText(*stringWorld, choose_font);
}

void TextView::healed() {
    textscene->setBackgroundBrush(QColor("green"));
    timer2.start();
}

void TextView::resetBg() {
    textscene->setBackgroundBrush(Qt::transparent);
}

void TextView::startTimer() {
    timer.start();
}

void TextView::stopTimer() {
    timer.stop();
    resetBg();
}

void TextView::moveCamera() {
    // cut world to size
    QString temp;
    qVecPlayer = qVec;
    auto before = ((world->getProtagonist()->getYPos() - 4) * 2) + 1;

    // take world edges into account
    if (before <= 0) {
        qVecPlayer = qVecPlayer.mid(before, 17 - before);
    } else
        qVecPlayer = qVecPlayer.mid(before, 17);

    for (int i = 0; i < qVecPlayer.size(); i++) {
        // take world edges into account
        before = (world->getProtagonist()->getXPos() - 7) * 4;
        if (before <= 0) {
            temp = qVecPlayer[i].mid(before, 60 - before);
        } else {
            temp = qVecPlayer[i].mid(before, 60);
        }
        temp.append("\n");
        qVecPlayer[i] = temp;
    }
}

void TextView::fighting() {
    textscene->setBackgroundBrush(QColor("orange"));
    timer2.start();
}

void TextView::activatePoisoned() {
    textscene->setBackgroundBrush(QColor("purple"));
    timer2.start();
    timer.start();
}
