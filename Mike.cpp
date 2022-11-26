//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(int hp, int speed, int points, int coins, int armor, bool bubble, int streak) : GameCharacter(hp, speed,
                                                                                                         points, coins,
                                                                                                         armor,
                                                                                                         bubble),
                                                                                           killStreak(streak) {
    //spawning mike
    std::string fileName = "res/textures/mike.png";
    try {
        if (!texture.loadFromFile(fileName))
            throw GameException("Error opening Mike texture file", fileName, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(5 * 32, 5 * 32));
    //sprite.setScale(sf::Vector2f(1.5, 1.5));
    pos = {(5 * 32) + 16, (5 * 32) + 16}; //this updates coordinates in PosEntity, (+16 for center of sprite)


    //mike's frame position (in pixel)
    idle.reserve(1);
    idle = {
            {0 * 32, 0 * 32, 32, 32},
    };

    sprite.setTextureRect(currentAnimation.getCurrentRect());
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
    float frameDuration = 0.5f;

    if (((offset.y > 0) && (offset.x > 0)) ||
        ((offset.y > 0) && (offset.x < 0))) //correct animation for diagonal movements
        currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
    else if (((offset.y < 0) && (offset.x > 0)) || ((offset.y < 0) && (offset.x < 0)))
        currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
    else {
        if (offset.x > 0)
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
        else if (offset.x < 0)
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
        if (offset.y > 0)
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
        else if (offset.y < 0)
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
    }

    sprite.setPosition(sprite.getPosition() + offset);
    pos += offset;
}

