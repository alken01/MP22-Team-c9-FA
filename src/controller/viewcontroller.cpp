#include "viewcontroller.h"
#include <iostream>
ViewController::ViewController(std::shared_ptr<WorldModel> world)
    : _QTextView(std::make_shared<QGraphicsView>()),
      _QGraphicsView(std::make_shared<QGraphicsView>()){
    this->world = world;
}

void ViewController::drawWorlds() {
    textView = std::make_shared<TextView>(world, _QTextView);
    render();
    switchToText();
}

// mapchanger
void ::ViewController::changeMap() {
    drawWorlds();
}

void ViewController::render() {
    textView->draw();
}

void ViewController::poisoned(){
    textView->setPoisoned();
}

void ViewController::healed(){
    textView->setHealed();
}

void ViewController::fighting(){
    textView->setFighting();
}

void ViewController::dead() {
    std::cout << "You died!" << std::endl;
    delayTimer.start(1000);
    delaySwitch = 1;
}

void ViewController::resetDelay() {
    delaySwitch = 0;
}


const std::shared_ptr<QGraphicsView>& ViewController::getQTextView() const {
    return _QTextView;
}
const std::shared_ptr<QGraphicsView>& ViewController::getQGraphicsView() const {
    return _QGraphicsView;
}

void ViewController::setWorld(std::shared_ptr<WorldModel> world) {
    this->world = world;
}

void ViewController::switchToGraphic() {
    _QGraphicsView.get()->setVisible(true);
    _QTextView.get()->setVisible(false);
}

void ViewController::switchToText() {
    _QGraphicsView.get()->setVisible(false);
    _QTextView.get()->setVisible(true);
}

void ViewController::switchViews() {
    bool isTextView = _QTextView.get()->isVisible();
    if (isTextView) {
        switchToGraphic();
    } else {
        switchToText();
    }
}