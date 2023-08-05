#ifndef WORLD_H
#define WORLD_H

#include <QImage>
#include <QObject>
#include <exception>
#include <memory>
#include <vector>
#include "world_global.h"

#include <iostream>
class WORLDSHARED_EXPORT Tile {
    public:
        enum Type {
            ConsumedHealthpack = -2,
            DefeatedEnemy = -1,
            NormalTile = 0,
            Wall,
            Healthpack,
            Enemy,
            PEnemy,
            XEnemy,
            Protagonist
        };

        struct Coordinates {
                int xPos;
                int yPos;
                Coordinates() : xPos(0), yPos(0) {}
                Coordinates(int xPos, int yPos) : xPos(xPos), yPos(yPos) {}
        };

        Coordinates getCoordinates() const { return Coordinates(xPos, yPos); }
        void setCoordinates(Coordinates newCoordinates) {
            setXPos(newCoordinates.xPos);
            setYPos(newCoordinates.yPos);
        }

        Tile(int xPosition, int yPosition, float tileWeight);
        virtual ~Tile() = default;
        float getValue() const { return value; };
        void setValue(float newValue) { value = newValue; };
        int getXPos() const { return xPos; };
        int getYPos() const { return yPos; };
        void setXPos(int newPos) { xPos = newPos; };
        void setYPos(int newPos) { yPos = newPos; }
        bool operator==(const Tile& other) const {
            return (getXPos() == other.getXPos()) &&
                   (getYPos() == other.getYPos());
        };
        virtual std::string serialize();
        Tile::Type getTileType() const {
            std::cout << "Tile: " << this->getValue() << std::endl;
            if (this->getValue() == INFINITY) return Tile::Wall;
            if (this->getValue() > 1) return Tile::Healthpack;
            if (this->getValue() == -1) return Tile::ConsumedHealthpack;
            return Tile::NormalTile;
        }

    protected:
        int xPos;
        int yPos;
        float value;
};

class WORLDSHARED_EXPORT Enemy : public QObject, public Tile {
        Q_OBJECT
    public:
        Enemy(int xPosition, int yPosition, float strength);
        ~Enemy() override = default;
        bool getDefeated() const { return defeated; }
        void setDefeated(bool value) {
            defeated = value;
            if (defeated) emit dead();
        };
        std::string serialize() override;
        Tile::Type getTileType() const  {
            if (this->getValue() == -1) return Tile::DefeatedEnemy;
            return Tile::Enemy;
        }

    signals:
        void dead();

    private:
        bool defeated;  // false by construction
};

class WORLDSHARED_EXPORT PEnemy : public Enemy {
        Q_OBJECT
    public:
        PEnemy(int xPosition, int yPosition, float strength);
        ~PEnemy() override = default;
        float getPoisonLevel() const;
        void setPoisonLevel(float value);
        std::string serialize() override;
        Tile::Type getTileType() const  {
            if (this->getValue() == -1) return Tile::DefeatedEnemy;
            std::cout << "PEnemy" << std::endl;
            return Tile::PEnemy;
        }

    public slots:
        bool poison();

    signals:
        void poisonLevelUpdated(int value);

    private:
        float poisonLevel;
};

class WORLDSHARED_EXPORT Protagonist : public QObject, public Tile {
        Q_OBJECT
    public:
        Protagonist();
        void setXPos(int newPos) {
            if (xPos != newPos) {
                xPos = newPos;
                emit posChanged(xPos, yPos);
            }
        }
        void setYPos(int newPos) {
            if (yPos != newPos) {
                yPos = newPos;
                emit posChanged(xPos, yPos);
            }
        }
        void setPos(int newX, int newY) {
            if (xPos != newX || yPos != newY) {
                xPos = newX;
                yPos = newY;
                emit posChanged(xPos, yPos);
            }
        }
        float getHealth() const { return health; };
        void setHealth(float value) {
            health = value;
            emit healthChanged(static_cast<int>(health));
        }

        float getEnergy() const { return energy; }
        void setEnergy(float value) {
            energy = value;
            emit energyChanged(static_cast<int>(energy));
        }
        std::string serialize() override;

        void decreaseEnergy(float damageValue) {
            float newEnergy = this->getEnergy() - damageValue;
            this->setEnergy(std::max(newEnergy, 0.0f));
        }

        void decreaseHealth(float damageValue) {
            float newHealth = this->getHealth() - damageValue;
            this->setHealth(std::max(newHealth, 0.0f));
        }

        void increaseEnergy(float addedValue) {
            float newEnergy = this->getEnergy() + addedValue;
            this->setEnergy(std::min(newEnergy, 100.0f));
        }

        void increaseHealth(float addedValue) {
            float newHealth = this->getHealth() + addedValue;
            this->setHealth(std::min(newHealth, 100.0f));
        }

        Tile::Type getTileType() const {
            return Tile::Protagonist;
        }

    signals:
        void posChanged(int x, int y);
        void healthChanged(int h);
        void energyChanged(int e);

    private:
        float health;  // 100.0f by construction
        float energy;  // 100.0f by construction
};

class WORLDSHARED_EXPORT World {
    public:
        World() = default;
        // createWorld may throw a std::logic_error exception
        // pRatio is the percentage PEnemies of the total number of enemies
        void createWorld(QString filename, unsigned int nrOfEnemies,
                         unsigned int nrOfHealthpacks, float pRatio = 0.25f);
        std::vector<std::unique_ptr<Tile>> getTiles();
        std::vector<std::unique_ptr<Enemy>> getEnemies();
        std::vector<std::unique_ptr<Tile>> getHealthPacks();
        std::unique_ptr<Protagonist> getProtagonist() const;
        int getRows() const { return rows; };
        int getCols() const { return cols; };

    private:
        int rows, cols;
        QImage world;
        std::vector<std::unique_ptr<Tile>> tiles;
        std::vector<std::unique_ptr<Enemy>> enemies;
        std::vector<std::unique_ptr<Tile>> healthPacks;
};

#endif  // WORLD_H
