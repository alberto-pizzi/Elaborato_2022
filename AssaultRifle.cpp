//
// Created by alber on 12/12/2022.
//

#include "AssaultRifle.h"

void AssaultRifle::shoot(const sf::Vector2f &normalizedBulletDir) {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    //shoot ONE bullet
    bullets.emplace_back(new AssaultRifleBullet(bulletTexture, 1700, barrelHole, this->weaponSprite.getPosition(),
                                                this->degrees, this->weaponSprite.getOrigin(),
                                                this->weaponSprite.getScale(), normalizedBulletDir));
    shotClock.restart();

    this->magazine.remainingBullets--;
}

AssaultRifle::AssaultRifle(bool equipped, const sf::Texture &handgunTexture,
                           const sf::Texture &assaultRifleBulletTexture,
                           int totBullets, int damage, sf::Time shotDelay, float reloadTime, int magazineCapacity,
                           int remainingBullets) : Weapon(
        equipped,
        handgunTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectAssaultShotSize,
        "assaultRifle",
        false) {

    //these values are used to give the correct starting point for centering on the player's shoulder
    this->startCenterForTranslation[LEFT] = {-16, 21};
    this->startCenterForTranslation[RIGHT] = {16, 21};
    this->startCenterForTranslation[UP] = {32, 21};
    this->startCenterForTranslation[DOWN] = {24, 21};



    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, this->fileTextureRectAssaultShotSize.x, this->fileTextureRectAssaultShotSize.y},
    };

    weaponSprite.setTextureRect({0, 0, this->fileTextureRectAssaultShotSize.x, this->fileTextureRectAssaultShotSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * this->fileTextureRectAssaultShotSize.x, 0, this->fileTextureRectAssaultShotSize.x,
                          this->fileTextureRectAssaultShotSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * this->fileTextureRectAssaultReloadSize.x, 1 * this->fileTextureRectAssaultReloadSize.y,
                            this->fileTextureRectAssaultReloadSize.x,
                            this->fileTextureRectAssaultReloadSize.y);

    //these values are the hit box weapon size from texture file
    this->hitBox.setSize(sf::Vector2f(66, 30));

    //set bullet texture
    this->bulletTexture = assaultRifleBulletTexture;
}
