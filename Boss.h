//
// Created by Alberto Pizzi on 31/12/22.
//

#ifndef ELABORATO_BOSS_H
#define ELABORATO_BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
private:
    sf::Vector2f scaleSize;
    static unsigned int roundCount; //this attribute is increased each boss round
public:
    //FIXME fix speed because after some time the sprites overlap them
    Boss(const sf::Texture &bossTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
         const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
         float hitProbability, float hp = 50, sf::Vector2f scaleSize = {3, 3}, bool animated = true,
         float speed = 200.f, unsigned int points = 100, unsigned int coins = 12, int armor = 10, bool bubble = false);
};


#endif //ELABORATO_BOSS_H
