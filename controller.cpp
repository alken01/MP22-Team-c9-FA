#include "controller.h"
#include <iostream>
#include "astar.h"

Controller::Controller(std::shared_ptr<WorldModel> w, std::shared_ptr<GraphicalView> g, std::shared_ptr<TextView> t) :
    graphical_view(g), text_view(t){
    this->world = w;
    this->graphical_view = g;
    this->text_view = t;
    this->Qtext_view = std::make_shared<QGraphicsView>();
    this->Qgraphics_view = std::make_shared<QGraphicsView>();

    //command list - add new commands here
    commands.push_back("up");
    commands.push_back("down");
    commands.push_back("left");
    commands.push_back("right");
    commands.push_back("goto x y");
    commands.push_back("goto enemy");
    commands.push_back("goto hp");
    commands.push_back("help");

    //mapList
    mapList.append("maze1");
    mapList.append("maze2");
    mapList.append("maze3");
    mapList.append("worldmap");
    mapList.append("worldmap4");
    //also create QStringlist for use in autofill and switch
    for(unsigned long i = 0; i < commands.size(); i++){
        completerList.append(commands.at(i));
    }
}

void Controller::handleInput(){}

void Controller::update(){}

void Controller::initWorlds(){
    this->world->getProtagonist()->setXPos(5);
    this->world->getProtagonist()->setYPos(5);
    this->text_view->draw(this->world, this->Qtext_view);
    this->graphical_view->draw(this->world, this->Qgraphics_view);
}

void::Controller::changeMap(QString mapName){
    QString init_worldmap = ":/images/world_images/" + mapName + ".png";
    auto test = std::make_shared<World>();
    test->createWorld(init_worldmap, 100, 100, 0.5);
    auto wm = std::make_shared<WorldModel>(test);
    this->world->getProtagonist()->setHealth(100);
    this->world->getProtagonist()->setEnergy(100);
    text_view->stopTimer();
    this->alive = 1;
    this->poisoned = 0;

    this->world = wm;
    initWorlds();
}

const std::shared_ptr<QGraphicsView>& Controller::getQgraphics_view() const{
    return Qgraphics_view;
}

void Controller::setQgraphics_view(const std::shared_ptr<QGraphicsView>& newQgraphics_view){
    Qgraphics_view = newQgraphics_view;
}

const std::shared_ptr<WorldModel>& Controller::getWorld() const{
    return world;
}

void Controller::setWorld(const std::shared_ptr<WorldModel>& newWorld){
    world = newWorld;
}

const std::shared_ptr<QGraphicsView>& Controller::getQtext_view() const{
    return Qtext_view;
}

void Controller::setQtext_view(const std::shared_ptr<QGraphicsView>& newQtext_view){
    Qtext_view = newQtext_view;
}

const std::shared_ptr<TextView>& Controller::getText_view() const{
    return text_view;
}

void Controller::setText_view(const std::shared_ptr<TextView>& newText_view){
    text_view = newText_view;
}

//checks input from text and gets matching unique command
QString Controller::commandReceived(QString input){
    int count = 0;
    std::vector<QString> resultSet;

    if(input.size() >= 4){
        if(input.left(4) == "goto"){
            cout << "yes" << endl;
            goto_helper(input);
            return NULL;
        }
    }

    for(unsigned long i = 0; i < commands.size(); ++i){
        for(int j = 0; j < input.size(); ++j){
            if(j < commands[i].size()){
                if(input.at(j) == commands[i].at(j)){
                    count++;
                }
            }
        }
        if(count == input.size()){
            resultSet.push_back(commands[i]);
        }
        count = 0;
    }

    if(resultSet.size() == 1){
        QString result = resultSet[0];
        std::cout << result.toStdString() << std::endl;
        movePlayer(result);
        return result;
    }
    return NULL;
}

void Controller::movePlayer(QString input){
    if(alive != 1){
        return;
    }
    //store old coordinate
    int x = world->getProtagonist()->getXPos();
    int y = world->getProtagonist()->getYPos();

    //new coordinate
    int x2 = x;
    int y2 = y;

    //follows order of commands added
    switch(completerList.indexOf(input)){
    case 0: //up
        y2--; break;
    case 1: //down
        y2++; break;
    case 2: //left
        x2--; break;
    case 3: //right
        x2++; break;
    case 5: //help handled in window
        return;
    default:
        std::cout << "This is not a legal move" << std::endl;
    }
    //if its a player move code below runs, otherwise return in switch statement
    if(x2 < 0 || y2 < 0 || x2 >= world->getWidth() || y2 >= world->getHeight()){ return; }

    // 0 health,1 enemy, 2 poison enemy, 3 wall, 4 tile
    auto test = checkMove(x2, y2);

    if(test == 3){
        std::cout.flush();
        std::cout << "you can't walk through walls" << std::endl;
        return;
    }

    else if(test == 2){
        std::cout.flush();
        std::cout << "encountered poison enemy" << std::endl;
    }

    else if(test == 1){
        std::cout.flush();
        std::cout << "encountered enemy" << std::endl;
    }

    else if(test == 0){
        std::cout.flush();
        std::cout << "got healt yay" << std::endl;
    }

    world->getProtagonist()->setXPos(x2);
    world->getProtagonist()->setYPos(y2);

    this->text_view->movProtagonist(x, y, world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos(), world);

    //check if alive
    if(world->getProtagonist()->getHealth() <= 0){
        dead(x2, y2);
    }

    if(world->getProtagonist()->getEnergy() <= 0){
        dead(x2, y2);
    }

    this->text_view->updateView();
}


void Controller::goto_helper(QString input){
    QStringList strList = input.split(" ");

    QString strX = strList.last();  // gets the last substring
    bool ok;
    int x = strX.toInt(&ok);        // convert the QString to an int, store the result in x

    if(!ok){

        if(strX == "hp"){
            goToHealthpack();
            return;
        } else if(strX == "enemy"){
            goToEnemy();
            return;
        }
        qDebug() << "Error converting string to int";
        return;
    }

    strList.removeLast();           // removes the last item from the list
    QString strY = strList.last();  // gets the second-to-last substring


    int y = strY.toInt(&ok);
    if(!ok){
        qDebug() << "Error converting string to int";
        return;
    }
    //call the helper function
    goToPath(x, y);
}

void Controller::goToEnemy(){
    auto world = this->getWorld();
    Tile start(world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos(), 0.0);
    vector<pair<int, int> > enemy_path = {};
    //max int value, yeah not the most elegant :(
    int min_len = 2147483647;
    //find the path with the smallest length
    for(unsigned long i = 0; i < world->getEnemies().size(); ++i){
        if(world->getEnemies().at(i)->getValue() == -1){
            continue;
        }
        int x = world->getEnemies().at(i)->getXPos();
        int y = world->getEnemies().at(i)->getYPos();
        Tile end(x, y, 0.0);
        vector<pair<int, int> > path = astar(world->getTiles(), world->getHeight(), world->getWidth(), start, end, 0.1);
        if(path.size() < min_len){
            enemy_path = path;
        }
    }
    //didnt find healthpacks
    if(enemy_path.empty()){
        return;
    }
    vector<QString> textPath = pathToText(enemy_path);
    for(const auto& input : textPath){
        movePlayer(input);
    }
}

void Controller::goToHealthpack(){
    auto world = this->getWorld();
    Tile start(world->getProtagonist()->getXPos(), world->getProtagonist()->getYPos(), 0.0);
    vector<pair<int, int> > health_pack = {};
    //max int value, yeah not the most elegant :(
    int min_len = 2147483647;
    //find the path with the smallest length
    for(unsigned long i = 0; i < world->getHealthPacks().size(); ++i){
        if(world->getHealthPacks().at(i)->getValue() == -1){
            continue;
        }
        int x = world->getHealthPacks().at(i)->getXPos();
        int y = world->getHealthPacks().at(i)->getYPos();
        Tile end(x, y, 0.0);
        vector<pair<int, int> > path = astar(world->getTiles(), world->getHeight(), world->getWidth(), start, end, 0.1);
        if(path.size() < min_len){
            health_pack = path;
        }
    }
    //didnt find healthpacks
    if(health_pack.empty()){
        return;
    }

    vector<QString> textPath = pathToText(health_pack);
    for(const auto& input : textPath){
        movePlayer(input);
    }
}

void Controller::goToPath(int x, int y){
    auto w = this->getWorld();
    Tile start(w->getProtagonist()->getXPos(), w->getProtagonist()->getYPos(), 0.0);
    Tile end(x, y, 0.0);
    vector<pair<int, int> > path = astar(w->getTiles(), w->getHeight(), w->getWidth(), start, end, 0.1);
    vector<QString> textPath = pathToText(path);
    for(const auto& input : textPath){
        movePlayer(input);
    }
}

vector<QString> Controller::pathToText(vector<pair<int, int> > path){
    // Resulting vector of directions
    std::vector<QString> directions;

    // Loop through the path and convert each pair of coordinates into a direction
    for(size_t i = 1; i < path.size(); i++){
        // Get the current and previous coordinates
        auto current = path[i];
        auto prev = path[i - 1];

        // Compare the coordinates and add the corresponding direction to the result vector
        if(current.first > prev.first){
            directions.push_back(QString("right"));
        } else if(current.first < prev.first){
            directions.push_back(QString("left"));
        } else if(current.second > prev.second){
            directions.push_back(QString("down"));
        } else if(current.second < prev.second){
            directions.push_back(QString("up"));
        }
    }

    // Return the vector of directions
    return directions;
}

int Controller::checkMove(int x, int y){
    auto test = world.get()->getWorldMap().at(x).at(y);

    //beaten enemy or used healthpack = -1 nothing happens
    if(test->getValue() == -1){
        return 4; //
    }

    //WALL
    if(test->getValue() == INFINITY){
        return 3; //is wall
    }

    //POISONED
    if(poisoned > 0){
        poisoned--; //one tile less poisoned
        world->getProtagonist()->setHealth(world->getProtagonist()->getHealth() - 1);
    } else text_view->stopTimer(); //stop poison effect

    //TILE + beaten enemy or used healthpack = -1
    if(test->getValue() <= 1 && test->getValue() >= 0){
        world->getProtagonist()->setEnergy(world->getProtagonist()->getEnergy() - test->getValue());

        return 4; //is tilethis->textscene->addText(*stringWorld,QFont("Monospace"));
    }


    //HEALTHPACK
    for(unsigned long i = 0; i < world->getHealthPacks().size(); ++i){
        int x = world->getHealthPacks().at(i)->getXPos();
        int y = world->getHealthPacks().at(i)->getYPos();
        if(test->getXPos() == x && test->getYPos() == y){

            //adding health
            auto health = world->getProtagonist()->getHealth();

            std::cout.flush();
            std::cout << "health added " << test->getValue() << std::endl;

            if(health + test->getValue() >= 100){
                world->getProtagonist()->setHealth(100);
            } else world->getProtagonist()->setHealth(health + test->getValue());

            text_view->healed();

            test->setValue(-1); //used
            return 0; // is health
        }
    }

    //POISON ENEMY
    if(std::dynamic_pointer_cast<PEnemy>(test)){

        std::cout.flush();
        std::cout << "Poisoned for:" << test->getValue() << std::endl;

        poisoned += test->getValue();
        world->getProtagonist()->setEnergy(100);
        test->setValue(-1); //beaten

        //start poison textview animation
        text_view->startTimer();

        return 2; //is poison enemy
    }


    //NORMAL ENEMY
    if(std::dynamic_pointer_cast<Enemy>(test)){

        std::cout.flush();
        std::cout << "damage added " << test->getValue() << std::endl;

        //damage done
        world->getProtagonist()->setHealth(world->getProtagonist()->getHealth() - test->getValue());
        world->getProtagonist()->setEnergy(100);
        test->setValue(-1); //beaten
        return 1; //is normal enemy
    }
    return -2;
}

void Controller::dead(int x, int y){
    this->text_view->protDead(x, y);
    text_view->stopTimer();
    this->alive = 0;
}

const QStringList& Controller::getMapList() const{
    return mapList;
}

void Controller::setMapList(const QStringList& newMapList){
    mapList = newMapList;
}

const QStringList& Controller::getCompleterList() const{
    return completerList;
}

void Controller::setCompleterList(const QStringList& newCompleterList){
    completerList = newCompleterList;
}

const std::vector<QString>& Controller::getCommands() const{
    return commands;
}

void Controller::setCommands(const std::vector<QString>& newCommands){
    commands = newCommands;
}

int Controller::getPoisoned() const{
    return poisoned;
}

void Controller::setPoisoned(int newPoisoned){
    poisoned = newPoisoned;
}

int Controller::getAlive() const{
    return alive;
}

void Controller::setAlive(int newAlive){
    alive = newAlive;
}

