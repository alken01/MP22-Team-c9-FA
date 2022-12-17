#include "xenemy.h"
#include <random>

XEnemy::XEnemy(int xPosition, int yPosition, float strength): Enemy(xPosition,yPosition,strength)
{
    //generate random energy value
    std::random_device rd;     // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(1,30); // Guaranteed unbiased

    energy = uni(rng);
}

float XEnemy::getEnergy() const
{
    return energy;
}

void XEnemy::setEnergy(float newEnergy)
{
    energy = newEnergy;
}
