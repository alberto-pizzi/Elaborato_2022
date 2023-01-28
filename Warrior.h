//
// Created by alber on 31/12/2022.
//

#ifndef ELABORATO_WARRIOR_H
#define ELABORATO_WARRIOR_H

#include "Enemy.h"

class Warrior : public Enemy {
private:
    float defense;
    sf::Texture warriorWithShieldTex;
    sf::Texture warriorWithoutShieldTex;
    bool textureChanged = false;
public:
    Warrior(const sf::Texture &noShieldedTex, const sf::Texture &shieldedTex, const sf::Vector2i &spawnTile,
            const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, float defense, sf::Vector2f damageHit,
            const std::vector<std::vector<Node>> &nodeMap, float hitProbability, bool animated = true, float hp = 20,
            float speed = 230.f, unsigned int points = 10, unsigned int coins = 2, float armor = 5);

    void receiveDamage(float damagePoints) override;
};


#endif //ELABORATO_WARRIOR_H
