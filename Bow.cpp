//
// Created by alber on 13/01/2023.
//

#include "Bow.h"

void Bow::shoot(const sf::Vector2f &normalizedBulletDir) {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    //shoot ONE bullet

    bullets.emplace_back(new Arrow(bulletTexture, 900, barrelHole, weaponSprite.getPosition(),
                                   degrees, weaponSprite.getOrigin(),
                                   weaponSprite.getScale(), normalizedBulletDir));

    shotClock.restart();
    animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
}

Bow::Bow(bool equipped, const sf::Texture &bowTexture, const sf::Texture &arrowTexture,
         int totBullets,
         int damage, sf::Time shotDelay, float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(
        equipped,
        bowTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectHandgunSize,
        "bow",
        true) {
    //these values are used to give the correct starting point for centering on the player's shoulder
    startCenterForTranslation[LEFT] = {-16, 21};
    startCenterForTranslation[RIGHT] = {16, 21};
    startCenterForTranslation[UP] = {32, 21};
    startCenterForTranslation[DOWN] = {24, 21};

    this->weaponSprite.setScale(sf::Vector2f(1.5, 1.5));

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, fileTextureRectHandgunSize.x, fileTextureRectHandgunSize.y},
    };

    weaponSprite.setTextureRect({0, 0, fileTextureRectHandgunSize.x, fileTextureRectHandgunSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * fileTextureRectHandgunSize.x, 0, fileTextureRectHandgunSize.x,
                          fileTextureRectHandgunSize.y);
/*
    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * fileTextureRectHandgunSize.x, 1 * fileTextureRectHandgunSize.y,
                            fileTextureRectHandgunSize.x,
                            fileTextureRectHandgunSize.y);
                            */

    //these values are the hit box weapon size from texture file
    hitBox.setSize(sf::Vector2f(24, 20));

    //set bullet texture
    bulletTexture = arrowTexture;
}