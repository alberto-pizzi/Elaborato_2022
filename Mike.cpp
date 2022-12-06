//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(const sf::Texture &mikeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, bool animated, int hp, float speed, unsigned int points, unsigned int coins,
           int armor,
           bool bubble, int streak) : GameCharacter(mikeTexture, hp,
                                                    speed,
                                                    points, spawnTile,
                                                    tileSize, rectSkin, animated,
                                                    coins,
                                                    armor,
                                                    bubble),
                                      killStreak(streak) {
    //this->sprite.setScale(sf::Vector2f(1.5,1.5));
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

void Mike::drawEntity(sf::RenderWindow &window) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}

void Mike::move(const sf::Vector2f &offset, float dt) {
    float newSpeed = this->speed;
    sf::Vector2f effectiveOffset;

    //set diagonal speed
    if (((offset.y > 0) && (offset.x > 0)) || ((offset.y > 0) && (offset.x < 0)) ||
        ((offset.y < 0) && (offset.x > 0)) || ((offset.y < 0) && (offset.x < 0)))
        newSpeed /= std::sqrt(2.f);

    effectiveOffset = offset * newSpeed * dt;
    sprite.setPosition(sprite.getPosition() + effectiveOffset);
    pos += effectiveOffset;
}

void Mike::directionInput(const sf::Vector2f &viewfinderPos) {
    //set Cartesian plane as player position
    sf::Vector2f origin = this->pos;
    sf::Vector2f translation = viewfinderPos - origin;
    float frameDuration = 0.5f;

    //when mouse exceeds bisects (+- 45°) of all quadrants, Mike changes body direction
    if (viewfinderPos.x >= origin.x) {
        if ((translation.y < translation.x) && (translation.y > -(translation.x)))
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
        else if (viewfinderPos.y >= origin.y)
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
        else if (viewfinderPos.y < origin.y)
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
    } else if (viewfinderPos.x < origin.x) {
        if ((translation.y > translation.x) && (translation.y < -(translation.x)))
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
        else if (viewfinderPos.y >= origin.y)
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
        else
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
    }
}

Mike::~Mike() = default;;

