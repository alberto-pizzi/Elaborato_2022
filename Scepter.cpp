//
// Created by alber on 25/01/2023.
//

#include "Scepter.h"

void Scepter::shoot(const sf::Vector2f &normalizedBulletDir) {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    //shoot ONE bullet
    sf::Vector2f bulletScale = {2, 2};
    //TODO implement critic bullet
    //FIXME chance bullet type

    bullets.emplace_back(new Bullet(bulletTexture, 600, weaponSprite.getOrigin(), degrees,
                                    weaponSprite.getScale(), normalizedBulletDir, weaponSprite.getPosition(),
                                    barrelHole, bulletScale));

    //play scepter shot sound
    audioManager.playSound("scepterShot");

    shotClock.restart();
    animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
}

Scepter::Scepter(bool equipped, const sf::Texture &scepterTex, const sf::Texture &energyBulletTex,
                 sf::Vector2f bossScale,
                 float damage, int totBullets, sf::Time shotDelay, float reloadTime, int magazineCapacity,
                 int remainingBullets) : Weapon(
        equipped,
        scepterTex,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectScepterSize,
        "scepter",
        true) {
    //these values are used to give the correct starting point for centering on the player's shoulder
    startCenterForTranslation[LEFT] = {-50, 65};
    startCenterForTranslation[RIGHT] = {70, 65};
    startCenterForTranslation[UP] = {60, 65};
    startCenterForTranslation[DOWN] = {60, 65};

    this->weaponSprite.setScale(sf::Vector2f(5, 5));

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, fileTextureRectScepterSize.x, fileTextureRectScepterSize.y},
    };

    weaponSprite.setTextureRect({0, 0, fileTextureRectScepterSize.x, fileTextureRectScepterSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * fileTextureRectScepterSize.x, 0, fileTextureRectScepterSize.x,
                          fileTextureRectScepterSize.y);
/*
    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * fileTextureRectScepterSize.x, 1 * fileTextureRectScepterSize.y,
                            fileTextureRectScepterSize.x,
                            fileTextureRectScepterSize.y);
                            */

    //these values are the hit box weapon size from texture file
    hitBox.setSize(sf::Vector2f(20, 23));

    //set bullet texture
    bulletTexture = energyBulletTex;
}