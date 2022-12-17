//
// Created by alber on 12/12/2022.
//

#include "AssaultRifle.h"

void AssaultRifle::shoot() {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);
    this->magazine.remainingBullets--;
    //std::cout<<"Remain bullets: "<<this->magazine.remainingBullets<<std::endl; //FIXME (only for debug)
    std::cout << "Remain bullets: " << this->totalBullets << std::endl;

}

AssaultRifle::AssaultRifle(bool equipped, const sf::Texture &handgunTexture, int totBullets, int damage,
                           float shotDelay, float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(
        equipped,
        handgunTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectAssaultShotSize,
        "AssaultRifle",
        false) {


    this->startCenterForTranslation[LEFT] = {-16, 21};
    this->startCenterForTranslation[RIGHT] = {16, 21};
    this->startCenterForTranslation[UP] = {32, 21};
    this->startCenterForTranslation[DOWN] = {24, 21};

    enum nFramesAssaultRifle {
        IDLE = 1, SHOT = 16, RELOAD = 17,
    };

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

    this->hitBox.setSize(sf::Vector2f(66, 30));
}
