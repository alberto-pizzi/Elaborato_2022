//
// Created by alber on 10/12/2022.
//

#include "Handgun.h"

void Handgun::shoot() {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);
    this->magazine.remainingBullets--;
    //std::cout<<"Remain bullets: "<<this->magazine.remainingBullets<<std::endl; //FIXME (only for debug)
}

Handgun::Handgun(bool equipped, const sf::Texture &handgunTexture, int totBullets, int damage, float shotDelay,
                 float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(equipped,
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
    //FIXME check texture file and magic numbers
    idleWeapon.reserve(1);
    idleWeapon = {
            {0, 0, this->fileTextureRectHandgunSize.x, this->fileTextureRectHandgunSize.y},
    };

    weaponSprite.setTextureRect({0, 0, this->fileTextureRectHandgunSize.x, this->fileTextureRectHandgunSize.y});

    shot.reserve(12);
    for (int i = 0; i < 12; i++)
        shot.emplace_back(i * this->fileTextureRectHandgunSize.x, 0, this->fileTextureRectHandgunSize.x,
                          this->fileTextureRectHandgunSize.y);

    reload.reserve(20);
    for (int i = 0; i < 20; i++)
        reload.emplace_back(i * this->fileTextureRectHandgunSize.x, 1 * this->fileTextureRectHandgunSize.y,
                            this->fileTextureRectHandgunSize.x,
                            this->fileTextureRectHandgunSize.y);

}
