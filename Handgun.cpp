//
// Created by alber on 10/12/2022.
//

#include "Handgun.h"

void Handgun::shoot() {

}

Handgun::Handgun(bool equipped, const sf::Texture &handgunTexture, int totBullets, int damage, float shotDelay,
                 float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(equipped, handgunTexture,
                                                                                        totBullets, damage, shotDelay,
                                                                                        reloadTime,
                                                                                        magazineCapacity,
                                                                                        remainingBullets,
                                                                                        fileTextureRectHandgunSize,
                                                                                        "Handgun") {

}
