//
// Created by alber on 31/12/2022.
//

#include "Warrior.h"

Warrior::Warrior(const sf::Texture &noShieldedTex, const sf::Texture &shieldedTex, const sf::Vector2i &spawnTile,
                 const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, float defense, sf::Vector2f damageHit,
                 const std::vector<std::vector<Node>> &nodeMap, float hitProbability, bool animated, float hp,
                 float speed,
                 unsigned int points, unsigned int coins, float armor)
        : Enemy(shieldedTex, hp, speed, points, spawnTile,
                tileSize, rectSkin, WARRIOR, damageHit, nodeMap, hitProbability, 2, animated,
                coins, armor), warriorWithShieldTex(shieldedTex), warriorWithoutShieldTex(noShieldedTex),
          defense(defense) {
    this->sprite.setScale(sf::Vector2f(1.75, 1.75));
}

void Warrior::receiveDamage(float damagePoints) {
    if (defense > 0) {
        float shieldDamage = defense - damagePoints;
        if (shieldDamage > 0)
            defense -= damagePoints;
        else {
            defense = 0;
            shieldDamage *= -1; //if negative, set it to positive
            Enemy::receiveDamage(shieldDamage);
        }
        //play bullet metal hit sound
        audioManager.playSound("metalHit");
    } else {
        if (!textureChanged) {
            sprite.setTexture(warriorWithoutShieldTex);
            textureChanged = true;
        }
        Enemy::receiveDamage(damagePoints);
    }
}

