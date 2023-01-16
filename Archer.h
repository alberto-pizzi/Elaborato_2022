//
// Created by alber on 13/01/2023.
//

#ifndef ELABORATO_ARCHER_H
#define ELABORATO_ARCHER_H

#include "Enemy.h"
#include "Bow.h"

class Archer : public Enemy {
public:
    Archer(const sf::Texture &archerTexture, const sf::Texture &bowTexture, const sf::Texture &arrowTexture,
           const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin,
           sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap, bool animated = true, float hp = 15,
           float speed = 200.f, unsigned int points = 5, unsigned int coins = 1, int armor = 0, bool bubble = false);

    void hit(GameCharacter &target) override;
};


#endif //ELABORATO_ARCHER_H
