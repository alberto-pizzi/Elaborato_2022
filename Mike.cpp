//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(int spawnTileX, int spawnTileY, int hp, float speed, int points, int coins, int armor, bool bubble,
           int streak) : GameCharacter(hp, speed,
                                       points,
                                       coins,
                                       armor,
                                       bubble),
                         killStreak(streak) {

    std::string fileName = "res/textures/mike.png";
    textureManager.loadTexture("mike", fileName);
    sprite.setTexture(textureManager.getTextureRef("mike"));
    //mike's frame position (in pixel)
    idle.reserve(1);
    idle = {
            {0 * 32, 0 * 32, 32, 32},
    };

    //spawning mike
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    sf::Vector2i spriteDimensions = {sprite.getTextureRect().width, sprite.getTextureRect().height};
    sf::Vector2f spriteCenter = {static_cast<float>(sprite.getTextureRect().width) / 2,
                                 static_cast<float>(sprite.getTextureRect().height) / 2};
    sprite.setPosition(sf::Vector2f(static_cast<float>(spawnTileX * spriteDimensions.x),
                                    static_cast<float>(spawnTileY * spriteDimensions.y)));
    pos = {(static_cast<float>(spawnTileX * spriteDimensions.x)) + spriteCenter.x,
           (static_cast<float>(spawnTileY * spriteDimensions.y)) +
           spriteCenter.y}; //this updates coordinates in PosEntity, (+16 for center of sprite)


    //WARNING: work here to edit frames
    goDown.reserve(3);
    goDown = {
            {0 * 32, 0 * 32, 32, 32},
            {1 * 32, 0 * 32, 32, 32},
            {2 * 32, 0 * 32, 32, 32},
    };

    goLeft.reserve(3);
    goLeft = {
            {0 * 32, 1 * 32, 32, 32},
            {1 * 32, 1 * 32, 32, 32},
            {2 * 32, 1 * 32, 32, 32},
    };

    goRight.reserve(3);
    goRight = {
            {0 * 32, 2 * 32, 32, 32},
            {1 * 32, 2 * 32, 32, 32},
            {2 * 32, 2 * 32, 32, 32},
    };

    goUp.reserve(3);
    goUp = {
            {0 * 32, 3 * 32, 32, 32},
            {1 * 32, 3 * 32, 32, 32},
            {2 * 32, 3 * 32, 32, 32},
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

