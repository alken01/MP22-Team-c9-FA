#include "constants.h"

const QColor Constants::POISONED_COLOR = QColor("purple");
const QColor Constants::HEALED_COLOR = QColor("green");
const QColor Constants::FIGHTING_COLOR = QColor("orange");
const int Constants::TIMER_ANIMATION = 1000;

const QChar Constants::WALL_SYMBOL = QChar(0x2588);         // █
const QChar Constants::DARKEST_SYMBOL = QChar(0x2593);      // ▓
const QChar Constants::DARKER_SYMBOL = QChar(0x2592);       // ▒
const QChar Constants::DARK_SYMBOL = QChar(0x2591);         // ░
const QChar Constants::EMPTY_SYMBOL = QChar(' ');           // _

const QChar Constants::PROTAGONIST_SYMBOL = QChar(0x263A);  // ☺
const QChar Constants::HEALTHPACK_SYMBOL = QChar(0x2665);   // ♥
const QChar Constants::ENEMY_SYMBOL = QChar(0x263B);        // ☻
const QChar Constants::PENEMY_SYMBOL = QChar(0x263C);       // ☼
const QChar Constants::XENEMY_SYMBOL = QChar(0x263D);       // ☽
const QChar Constants::DEAD_SYMBOL = QChar(0x2620);         // ☠

const std::unordered_map<Tile::Type, QChar> Constants::symbolMap = {
{Tile::Enemy, ENEMY_SYMBOL},
{Tile::PEnemy, PENEMY_SYMBOL},
{Tile::XEnemy, XENEMY_SYMBOL},
{Tile::Healthpack, HEALTHPACK_SYMBOL},
{Tile::Protagonist, PROTAGONIST_SYMBOL},
{Tile::Wall, WALL_SYMBOL},
{Tile::NormalTile, EMPTY_SYMBOL},
{Tile::DefeatedEnemy, DEAD_SYMBOL}};

QChar Constants::getSymbol(Tile::Type type) {
    auto it = symbolMap.find(type);
    if (it != symbolMap.end()) {
        return it->second;
    }
    return EMPTY_SYMBOL;  // Default symbol for unknown types
}
QChar Constants::grayscaleToASCII(float intensity) {
    if (intensity == INFINITY) return WALL_SYMBOL;
    if (intensity > 1) return HEALTHPACK_SYMBOL;
    if (intensity < 0.2) return DARKEST_SYMBOL;
    if (intensity < 0.5) return DARKER_SYMBOL;
    if (intensity < 0.8) return DARK_SYMBOL;
    return EMPTY_SYMBOL;
}