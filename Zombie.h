//
// Created by Alberto Pizzi on 29/12/22.
//

#ifndef ELABORATO_ZOMBIE_H
#define ELABORATO_ZOMBIE_H

#include "Enemy.h"

class Zombie : public Enemy {
public:
    Zombie(const sf::Texture &zombieTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
           float hitProbability, bool animated = true, float hp = 15, float speed = 210.f, unsigned int points = 5,
           unsigned int coins = 1, float armor = 0);

};


#endif //ELABORATO_ZOMBIE_H
