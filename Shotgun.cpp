//
// Created by alber on 13/12/2022.
//

#include "Shotgun.h"

void Shotgun::shoot(const sf::Vector2f &normalizedBulletDir) {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    //shoot ONE bullet
    bullets.emplace_back(new ShotgunBullet(bulletTexture, 1900, barrelHole, this->weaponSprite.getPosition(),
                                           this->degrees, this->weaponSprite.getOrigin(),
                                           this->weaponSprite.getScale(), normalizedBulletDir));
    shotClock.restart();

    std::cout << " bullets: " << this->bullets.size() << std::endl;
    this->magazine.remainingBullets--;
}

Shotgun::Shotgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &shotgunBulletTexture,
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
        fileTextureRectShotgunShotSize,
        "Shotgun",
        false) {


    this->startCenterForTranslation[LEFT] = {-16, 27};
    this->startCenterForTranslation[RIGHT] = {16, 27};
    this->startCenterForTranslation[UP] = {32, 27};
    this->startCenterForTranslation[DOWN] = {24, 27};

    enum totFramesShotgun {
        IDLE = 1, SHOT = 14, RELOAD = 14,
    };

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, this->fileTextureRectShotgunShotSize.x, this->fileTextureRectShotgunShotSize.y},
    };

    weaponSprite.setTextureRect({0, 0, this->fileTextureRectShotgunShotSize.x, this->fileTextureRectShotgunShotSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * this->fileTextureRectShotgunShotSize.x, 0, this->fileTextureRectShotgunShotSize.x,
                          this->fileTextureRectShotgunShotSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * this->fileTextureRectShotgunReloadSize.x, 2 * this->fileTextureRectShotgunReloadSize.y,
                            this->fileTextureRectShotgunReloadSize.x,
                            this->fileTextureRectShotgunReloadSize.y);

    this->hitBox.setSize(sf::Vector2f(70, 15));

    //set bullet texture
    this->bulletTexture = shotgunBulletTexture;

}
