//
// Created by alber on 10/01/2023.
//

#ifndef ELABORATO_ENEMY_H
#define ELABORATO_ENEMY_H

#include "GameCharacter.h"
#include "AI.h"
#include <thread>
#include <atomic>
#include <memory>

class Enemy : public GameCharacter {
private:
    std::atomic<bool> pathReady;
    std::vector<std::vector<Node>> nodeMap;
    float hitProbability; //as percentage (form 0 to 100)
protected:
    //the protected constructor is to make the class non-instantiable (like an abstract class)
    Enemy(const sf::Texture &tex, float hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
          const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
          const std::vector<std::vector<Node>> &nodeMap, float hitProbability, float hitRange = 5, bool animated = true,
          unsigned int coins = 0, int armor = 0, bool bubble = false);

public:
    std::shared_ptr<AI> ai;
    std::vector<Node> path;
    sf::Clock pathClock;
    sf::Time updatingPathTime = sf::seconds(1);
    bool firstTime = true;
    bool hasPath = false;
    std::thread pathfindingThread;


    void followPath(float dt, sf::Vector2i tileSize, const std::vector<std::unique_ptr<Enemy>> &enemies);

    void setPath(const std::vector<Node> &path);

    virtual void areaHit(std::vector<std::unique_ptr<Enemy>> &targets);

    void startPathfindingThread(sf::Vector2i startTile, sf::Vector2i targetTile);

    static void findPathWrapper(const std::shared_ptr<AI> &ai, sf::Vector2i startTile, sf::Vector2i targetTile,
                                std::vector<Node> &path,
                                std::atomic<bool> &pathReady);

    bool isPathReady();

    virtual bool
    isAbleToHit(const GameCharacter &target, const Dice &hitDice, float hitChance); //as percentage (form 0 to 100)

    bool isPositionOccupied(sf::Vector2f pos, const std::vector<std::unique_ptr<Enemy>> &enemies);
};


#endif //ELABORATO_ENEMY_H
