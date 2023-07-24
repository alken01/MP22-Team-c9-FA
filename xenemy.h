#ifndef XENEMY_H
#define XENEMY_H

#include <QObject>
#include "world.h"

class XEnemy : public Enemy
{
    Q_OBJECT
public:
    XEnemy(int xPosition, int yPosition, float strength);
    ~XEnemy() override = default;
    float getEnergy() const;
    void setEnergy(float newEnergy);

private:
    float energy;
};

#endif // XENEMY_H
