#ifndef XENEMY_H
#define XENEMY_H

#include <QObject>
#include "world.h"
#include "world_global.h"
#include <random>

class WORLDSHARED_EXPORT XEnemy : public Enemy {
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);
    float getEnergyLevel() const;
    void setEnergyLevel(float newEnergy);
    Tile::Type getTileType() const ;

private:
    float energy;
    static float generateRandomEnergy();
};

#endif  // XENEMY_H
