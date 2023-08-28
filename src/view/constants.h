#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QChar>
#include <QColor>
#include <unordered_map>
#include "world.h"

class Constants {
    public:
        static const QColor POISONED_COLOR;
        static const QColor HEALED_COLOR;
        static const QColor FIGHTING_COLOR;
        static const int TIMER_ANIMATION;

        static const QChar WALL_SYMBOL;
        static const QChar DARKEST_SYMBOL;
        static const QChar DARKER_SYMBOL;
        static const QChar DARK_SYMBOL;
        static const QChar EMPTY_SYMBOL;

        static const QChar PROTAGONIST_SYMBOL;
        static const QChar HEALTHPACK_SYMBOL;
        static const QChar ENEMY_SYMBOL;
        static const QChar PENEMY_SYMBOL;
        static const QChar XENEMY_SYMBOL;
        static const QChar DEAD_SYMBOL;

        static QChar getSymbol(Tile::Type type);
        static QChar grayscaleToASCII(float intensity);

        static const int TOTAL_ROWS = 18;
        static const int TOTAL_COLUMNS = 60;
        static const int Y_OFFSET = 5;
        static const int X_OFFSET = 7;

    private:
        static const std::unordered_map<Tile::Type, QChar> symbolMap;
};

#endif  // CONSTANTS_H
