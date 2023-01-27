//
// Created by alber on 31/12/2022.
//

#include "Warrior.h"

Warrior::Warrior(const sf::Texture &warriorTexture, const sf::Texture &shieldTexture, const sf::Vector2i &spawnTile,
                 const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, float defense, sf::Vector2f damageHit,
                 const std::vector<std::vector<Node>> &nodeMap, float hitProbability, bool animated, float hp,
                 float speed,
                 unsigned int points, unsigned int coins, float armor)
        : Enemy(warriorTexture, hp, speed, points, spawnTile,
                tileSize, rectSkin, WARRIOR, damageHit, nodeMap, hitProbability, 2, animated,
                coins, armor), shield(shieldTexture, defense) {
    this->sprite.setScale(sf::Vector2f(1.75, 1.75));
}

void Warrior::receiveDamage(float damagePoints) {
    if (shield.defense > 0) {
        float shieldDamage = shield.defense - damagePoints;
        if (shieldDamage > 0)
            shield.defense -= damagePoints;
        else {
            shield.defense = 0;
            shieldDamage *= -1; //if negative, set it to positive
            Enemy::receiveDamage(shieldDamage);
        }
        //play bullet metal hit sound
        audioManager.playSound("metalHit");
    } else
        Enemy::receiveDamage(damagePoints);
}

void Warrior::drawEntity(sf::RenderWindow &window, bool gameOver) {
    if (skinDirection[UP])
        shield.shieldSprite.setPosition({sprite.getPosition().x - 2, sprite.getPosition().y + 10});
    else if (skinDirection[LEFT])
        shield.shieldSprite.setPosition({sprite.getPosition().x + sprite.getGlobalBounds().width / 3 - 5,
                                         sprite.getPosition().y + sprite.getGlobalBounds().height / 2});
    else if (skinDirection[RIGHT])
        shield.shieldSprite.setPosition({sprite.getPosition().x + sprite.getGlobalBounds().width / 3,
                                         sprite.getPosition().y + sprite.getGlobalBounds().height / 2});
    else if (skinDirection[DOWN])
        shield.shieldSprite.setPosition({sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
                                         sprite.getPosition().y + +sprite.getGlobalBounds().height / 2});

    if (skinDirection[UP]) {
        if (shield.defense > 0)
            window.draw(shield.shieldSprite);
        GameCharacter::drawEntity(window, gameOver);
    } else {
        GameCharacter::drawEntity(window, gameOver);
        if (shield.defense > 0)
            window.draw(shield.shieldSprite);
    }
}

Warrior::Shield::Shield(const sf::Texture &shieldTexture, float defense) : shieldTexture(shieldTexture),
                                                                           defense(defense) {
    shieldSprite.setTexture(shieldTexture);
    shieldSprite.setScale(sf::Vector2f(0.5, 0.5));
}

