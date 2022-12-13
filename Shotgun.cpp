//
// Created by alber on 13/12/2022.
//

#include "Shotgun.h"

void Shotgun::shoot() {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);
    this->magazine.remainingBullets--;
    //std::cout<<"Remain bullets: "<<this->magazine.remainingBullets<<std::endl; //FIXME (only for debug)
    std::cout << "Remain bullets: " << this->totalBullets << std::endl;

}

Shotgun::Shotgun(bool equipped, const sf::Texture &handgunTexture, int totBullets, int damage, float shotDelay,
                 float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(equipped,
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
    //FIXME check texture file and magic numbers
    idleWeapon.reserve(1);
    idleWeapon = {
            {0, 0, this->fileTextureRectShotgunShotSize.x, this->fileTextureRectShotgunShotSize.y},
    };

    weaponSprite.setTextureRect({0, 0, this->fileTextureRectShotgunShotSize.x, this->fileTextureRectShotgunShotSize.y});

    shot.reserve(14);
    for (int i = 0; i < 14; i++)
        shot.emplace_back(i * this->fileTextureRectShotgunShotSize.x, 0, this->fileTextureRectShotgunShotSize.x,
                          this->fileTextureRectShotgunShotSize.y);

    reload.reserve(14);
    for (int i = 0; i < 14; i++)
        reload.emplace_back(i * this->fileTextureRectShotgunReloadSize.x, 2 * this->fileTextureRectShotgunReloadSize.y,
                            this->fileTextureRectShotgunReloadSize.x,
                            this->fileTextureRectShotgunReloadSize.y);
}
