//
// Created by alber on 10/01/2023.
//

#ifndef ELABORATO_ENEMY_H
#define ELABORATO_ENEMY_H

#include "GameCharacter.h"
#include "AI.h"

class Enemy : public GameCharacter {
protected:
    Enemy(const sf::Texture &tex, int hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
          const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
          const std::vector<std::vector<Node>> &nodeMap, float hitRange = 5, bool animated = true,
          unsigned int coins = 0, int armor = 0, bool bubble = false);

public:
    AI ai;
    std::vector<Node> path;
    int pathIndex = 0;

    void followPath(const std::vector<Node> &path);

    virtual void areaHit(std::vector<std::unique_ptr<Enemy>> &targets);
};


#endif //ELABORATO_ENEMY_H
