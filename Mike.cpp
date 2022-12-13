//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Vector2i &spawnTile,
           const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, bool animated, int hp, float speed,
           unsigned int points, unsigned int coins, int armor, bool bubble, int streak) : GameCharacter(mikeTexture, hp,
                                                                                                        speed,
                                                                                                        points,
                                                                                                        spawnTile,
                                                                                                        tileSize,
                                                                                                        rectSkin,
                                                                                                        animated,
                                                                                                        coins,
                                                                                                        armor,
                                                                                                        bubble),
                                                                                          killStreak(streak) {
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

    weapon = std::unique_ptr<Weapon>(new Handgun(true, handgunTexture));
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

void Mike::directionInput(const sf::Vector2f &viewfinderPos, bool &isUp) {
    //set Cartesian plane as player position
    sf::Vector2f origin = this->pos;
    sf::Vector2f translation = viewfinderPos - origin;
    float frameDuration = 0.5f;
    float radians, degrees;


    //weapon angle from input
    radians = std::atan(translation.y / translation.x);
    degrees = radians * static_cast<float>(180 / M_PI);
    weapon->weaponSprite.setPosition(this->sprite.getPosition().x + 18,
                                     this->sprite.getPosition().y + 21); //FIXME magic numbers
    //when mouse exceeds bisects (+- 45°) of all quadrants, Mike changes body direction
    if (viewfinderPos.x >= origin.x) {
        weapon->weaponSprite.setScale(sf::Vector2f(1, 1));
        if ((translation.y < translation.x) && (translation.y > -(translation.x))) {
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
            isUp = false;
        } else if (viewfinderPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            isUp = false;
        } else if (viewfinderPos.y < origin.y) {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            isUp = true;
        }
    } else if (viewfinderPos.x < origin.x) {
        weapon->weaponSprite.setScale(sf::Vector2f(-1, 1));
        if ((translation.y > translation.x) && (translation.y < -(translation.x))) {
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
            isUp = false;
        } else if (viewfinderPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            isUp = false;
        } else {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            isUp = true;
        }
    }

    if (weapon->getWeaponName() == "Handgun")
        weapon->weaponSprite.setOrigin(sf::Vector2f(0, 0));
    else if (weapon->getWeaponName() == "AssaultRifle")
        weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));
    else if (weapon->getWeaponName() == "Shotgun")
        weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));

    weapon->weaponSprite.setRotation(degrees);
}

void Mike::setWeaponPosToShouldersPos() { //FIXME magic numbers
    if (currentAnimation.frames == goRight)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[RIGHT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[RIGHT].y);
    else if (currentAnimation.frames == goLeft)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width +
                                         weapon->startCenterForTranslation[LEFT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[LEFT].y);
    else if (currentAnimation.frames == goUp)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[UP].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[UP].y);
    else if (currentAnimation.frames == goDown)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[DOWN].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[DOWN].y);
}

Mike::~Mike() = default;

