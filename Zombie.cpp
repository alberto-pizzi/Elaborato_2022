//
// Created by Alberto Pizzi on 29/12/22.
//

#include "Zombie.h"

Zombie::Zombie(const sf::Texture &zombieTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
               const sf::Vector2i &rectSkin, sf::Vector2f damageHit, bool animated, int hp, float speed,
               unsigned int points,
               unsigned int coins, int armor, bool bubble) : GameCharacter(zombieTexture, hp, speed, points, spawnTile,
                                                                           tileSize, rectSkin, ZOMBIE, damageHit, 2,
                                                                           animated,
                                                                           coins, armor, bubble) {
    this->sprite.setScale(sf::Vector2f(1.5, 1.5));
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

