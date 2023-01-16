//
// Created by alber on 31/12/2022.
//

#include "Warrior.h"

Warrior::Warrior(const sf::Texture &warriorTexture, const sf::Texture &shieldTexture, const sf::Vector2i &spawnTile,
                 const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, float defense, sf::Vector2f damageHit,
                 const std::vector<std::vector<Node>> &nodeMap, float hitProbability, bool animated, float hp,
                 float speed,
                 unsigned int points, unsigned int coins, int armor, bool bubble)
        : Enemy(warriorTexture, hp, speed, points, spawnTile,
                tileSize, rectSkin, WARRIOR, damageHit, nodeMap, hitProbability, 2, animated,
                coins, armor, bubble), shield(shieldTexture, defense) {
    this->sprite.setScale(sf::Vector2f(1.75, 1.75));
    //WARNING: work here to edit frames
    goDown.reserve(3);
    goDown = {
            {0 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goLeft.reserve(3);
    goLeft = {
            {0 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goRight.reserve(3);
    goRight = {
            {0 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goUp.reserve(3);
    goUp = {
            {0 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };
}

void Warrior::receiveDamage(float damagePoints) {
    if (shield.defense > 0) {
        float shieldDamage = shield.defense - damagePoints;
        if (shieldDamage > 0)
            shield.defense -= damagePoints;
        else {
            shield.defense = 0;
            shieldDamage *= -1; //if negative, set it to positive
            GameCharacter::receiveDamage(shieldDamage);
        }
    } else
        GameCharacter::receiveDamage(damagePoints);
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

