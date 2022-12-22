//
// Created by alber on 10/12/2022.
//

#include "Handgun.h"

void Handgun::shoot(const sf::Vector2f &normalizedBulletDir) {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    //shoot ONE bullet
    bullets.emplace_back(new HandgunBullet(bulletTexture, 1200, barrelHole, this->weaponSprite.getPosition(),
                                           this->degrees, this->weaponSprite.getOrigin(),
                                           this->weaponSprite.getScale(), normalizedBulletDir));
    shotClock.restart();
    this->magazine.remainingBullets--;
}

Handgun::Handgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
                 int totBullets,
                 int damage, sf::Time shotDelay, float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(
        equipped,
        handgunTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectHandgunSize,
        "Handgun",
        true) {
    this->startCenterForTranslation[LEFT] = {-16, 21};
    this->startCenterForTranslation[RIGHT] = {16, 21};
    this->startCenterForTranslation[UP] = {32, 21};
    this->startCenterForTranslation[DOWN] = {24, 21};

    enum totFramesHandgun {
        IDLE = 1, SHOT = 12, RELOAD = 17,
    };

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, this->fileTextureRectHandgunSize.x, this->fileTextureRectHandgunSize.y},
    };

    weaponSprite.setTextureRect({0, 0, this->fileTextureRectHandgunSize.x, this->fileTextureRectHandgunSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * this->fileTextureRectHandgunSize.x, 0, this->fileTextureRectHandgunSize.x,
                          this->fileTextureRectHandgunSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * this->fileTextureRectHandgunSize.x, 1 * this->fileTextureRectHandgunSize.y,
                            this->fileTextureRectHandgunSize.x,
                            this->fileTextureRectHandgunSize.y);


    this->hitBox.setSize(sf::Vector2f(40, 20)); //TODO check correctness

    //set bullet texture
    this->bulletTexture = handgunBulletTexture;
}
