//
// Created by alber on 10/12/2022.
//

#include "Handgun.h"

void Handgun::shoot() {
    std::cout << "SHOOT!" << std::endl;
    float frameDuration = 0.5f;
    currentAnimation.setMovementAnimation(shot, frameDuration);
}

Handgun::Handgun(bool equipped, const sf::Texture &handgunTexture, int totBullets, int damage, float shotDelay,
                 float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(equipped, handgunTexture,
                                                                                        totBullets, damage, shotDelay,
                                                                                        reloadTime,
                                                                                        magazineCapacity,
                                                                                        remainingBullets,
                                                                                        fileTextureRectHandgunSize,
                                                                                        "Handgun") {
    /*
    shot.reserve(12);
    for (int i=0;i<12;i++)
        shot.emplace_back(i * 64,0,64,32); //FIXME check texture file and magic numbers
        */
}
