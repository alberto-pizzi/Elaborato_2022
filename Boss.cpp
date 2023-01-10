//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Boss.h"

Boss::Boss(const sf::Texture &bossTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
           sf::Vector2f scaleSize, bool animated, int hp, float speed, unsigned int points, unsigned int coins,
           int armor,
           bool bubble) : Enemy(bossTexture,
                                hp, speed,
                                points,
                                spawnTile,
                                tileSize,
                                rectSkin, BOSS,
                                damageHit, nodeMap, 1,
                                animated,
                                coins, armor,
                                bubble) {
    this->sprite.setScale(sf::Vector2f(scaleSize));
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
