#include "world_global.h"
#include <vector>
#include <memory>
#include <QObject>
#include <QImage>
#include <exception>


#ifndef XENEMY_H
#define XENEMY_H

class WORLDSHARED_EXPORT XEnemy: public Enemy
{
    Q_OBJECT
public:
    PEnemy(int xPosition, int yPosition, float strength);
    ~PEnemy() override = default;
    float getPoisonLevel() const;
    void setPoisonLevel(float value);
    std::string serialize() override;

public slots:
    bool poison();

signals:
    void poisonLevelUpdated(int value);

private:
    float poisonLevel;
};

#endif // XENEMY_H
