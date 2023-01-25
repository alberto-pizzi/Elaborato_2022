//
// Created by Alberto Pizzi on 29/12/22.
//

#include "Zombie.h"

Zombie::Zombie(const sf::Texture &zombieTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
               const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
               float hitProbability, bool animated, float hp, float speed, unsigned int points, unsigned int coins,
               float armor, bool bubble)
        : Enemy(zombieTexture, hp, speed, points, spawnTile,
                tileSize, rectSkin, ZOMBIE, damageHit, nodeMap, hitProbability, 2,
                animated,
                coins, armor, bubble) {

}

