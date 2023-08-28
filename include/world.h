#ifndef WORLD_H
#define WORLD_H

#include <QImage>
#include <QObject>
#include <exception>
#include <memory>
#include <vector>
#include "coordinates.h"
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

        Tile(int xPosition, int yPosition, float tileWeight);
        virtual ~Tile() = default;
        float getValue() const { return value; }
        void setValue(float newValue) { value = newValue; }
        int getXPos() const { return coordinates.getX(); }
        int getYPos() const { return coordinates.getY(); }
        void setXPos(int newPos) { coordinates.setX(newPos); }
        void setYPos(int newPos) { coordinates.setY(newPos); }
        bool operator==(const Tile& other) const {
            return (getXPos() == other.getXPos()) &&
                   (getYPos() == other.getYPos());
        }
        virtual std::string serialize();

        Tile::Type getTileType() const {
            if (this->getValue() == INFINITY) return Tile::Wall;
            if (this->getValue() > 1) return Tile::Healthpack;
            if (this->getValue() == -1) return Tile::ConsumedHealthpack;
            return Tile::NormalTile;
        }

        Coordinates getCoordinates() const { return coordinates; }
        void setCoordinates(Coordinates newCoordinates) {
            coordinates = newCoordinates;
        }

    protected:
        Coordinates coordinates;
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
        Tile::Type getTileType() const {
            if (getDefeated()) return Tile::DefeatedEnemy;
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
        Tile::Type getTileType() const {
            // if (getDefeated()) return Tile::DefeatedEnemy;
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
            if (coordinates.getX() != newPos) {
                coordinates.setX(newPos);
                emit posChanged(coordinates.getX(), coordinates.getY());
            }
        }

        void setYPos(int newPos) {
            if (coordinates.getY() != newPos) {
                coordinates.setY(newPos);
                emit posChanged(coordinates.getX(), coordinates.getY());
            }
        }

        void setPos(int newX, int newY) {
            if (coordinates.getX() != newX || coordinates.getY() != newY) {
                coordinates.setX(newX);
                coordinates.setY(newY);
                emit posChanged(coordinates.getX(), coordinates.getY());
            }
        }

        float getHealth() const { return health; }
        void setHealth(float value) {
            health = std::max(0.0f, std::min(value, 100.0f));
            emit healthChanged(static_cast<int>(health));
        }

        float getEnergy() const { return energy; }
        void setEnergy(float value) {
            energy = std::max(0.0f, std::min(value, 100.0f));
            emit energyChanged(static_cast<int>(energy));
        }

        std::string serialize() override;

        void decreaseEnergy(float damageValue) {
            float newEnergy = this->getEnergy() - damageValue;
            this->setEnergy(newEnergy);
        }

        void decreaseHealth(float damageValue) {
            float newHealth = this->getHealth() - damageValue;
            this->setHealth(newHealth);
        }

        void increaseEnergy(float addedValue) {
            float newEnergy = this->getEnergy() + addedValue;
            this->setEnergy(newEnergy);
        }

        void increaseHealth(float addedValue) {
            float newHealth = this->getHealth() + addedValue;
            this->setHealth(newHealth);
        }

        bool isAlive() const { return health > 0 && energy > 0; }

        Tile::Type getTileType() const {
            if (!isAlive()) return Tile::DefeatedEnemy;
            return Tile::Protagonist;
        }

        void setPoison(int value) { poison = value; }
        int getPoison() const { return poison; }
        void increasePoison(int addPoison) { poison += addPoison; }
        void decreasePoison(int decreasePoison) { poison -= decreasePoison; }

    signals:
        void posChanged(int x, int y);
        void healthChanged(int h);
        void energyChanged(int e);

    private:
        float health;  // Ranges from 0.0f to 100.0f
        float energy;  // Ranges from 0.0f to 100.0f
        int poison = 0;
        Coordinates prevCoord;
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
