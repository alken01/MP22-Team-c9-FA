#ifndef COMMANDSMAP_H
#define COMMANDSMAP_H

#include <QHash>
#include <QString>
#include "coordinates.h"

class CommandsMap {
public:
    static Coordinates getMoveDirection(const QString& command) {
        return commandsMap().value(command.toLower(), Coordinates(0, 0));
    }

    static QList<QString> getCommands() {
        return commandsMap().keys();
    }

private:
    static QHash<QString, Coordinates>& commandsMap() {
        static QHash<QString, Coordinates> instance;
        if (instance.isEmpty()) {
            instance["up"] = Coordinates(0, -1);
            instance["down"] = Coordinates(0, 1);
            instance["left"] = Coordinates(-1, 0);
            instance["right"] = Coordinates(1, 0);
        }
        return instance;
    }
};

#endif // COMMANDSMAP_H
