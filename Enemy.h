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
protected:
    Enemy(const sf::Texture &tex, int hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
          const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
          const std::vector<std::vector<Node>> &nodeMap, float hitRange = 5, bool animated = true,
          unsigned int coins = 0, int armor = 0, bool bubble = false);

public:
    std::shared_ptr<AI> ai;
    std::vector<Node> path;
    int pathIndex = 0;
    sf::Clock pathClock;
    sf::Time updatingPathTime = sf::seconds(1);
    bool firstTime = true;
    bool hasPath = false;
    std::thread pathfindingThread;


    void followPath(float dt, sf::Vector2i tileSize);

    void setPath(const std::vector<Node> &path);

    virtual void areaHit(std::vector<std::unique_ptr<Enemy>> &targets);

    void startPathfindingThread(sf::Vector2i startTile, sf::Vector2i targetTile);

    static void findPathWrapper(const std::shared_ptr<AI> &ai, sf::Vector2i startTile, sf::Vector2i targetTile,
                                std::vector<Node> &path,
                                std::atomic<bool> &pathReady);

    bool isPathReady();
};


#endif //ELABORATO_ENEMY_H
