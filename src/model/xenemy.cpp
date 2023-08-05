#include "xenemy.h"
#include <iostream>

const int MIN_ENERGY = 1;
const int MAX_ENERGY = 30;

XEnemy::XEnemy(int xPosition, int yPosition, float strength)
    : Enemy(xPosition, yPosition, strength), energy(generateRandomEnergy()) {
}

float XEnemy::getEnergyLevel() const {
    return energy;
}

void XEnemy::setEnergyLevel(float newEnergy) {
    energy = newEnergy;
}

Tile::Type XEnemy::getTileType() const {
    if (getDefeated()) return Tile::DefeatedEnemy;
    return Tile::XEnemy;
}

float XEnemy::generateRandomEnergy() {
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());

    // Guaranteed unbiased
    std::uniform_int_distribution<int> uni(MIN_ENERGY, MAX_ENERGY);
    return static_cast<float>(uni(rng));
}
