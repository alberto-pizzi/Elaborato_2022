//
// Created by alber on 10/12/2022.
//

#include "Weapon.h"

bool Weapon::reloadWeapon() {
    return false;
}

Weapon::Weapon(bool equipped, int totBullets, int damage, float shotDelay, float reloadTime, int magazineCapacity,
               int remainingBullets, const sf::Vector2i &texRectWeapon)
        : equipped(equipped), totalBullets(totBullets), damage(damage), nextShotDelay(shotDelay),
          reloadTime(reloadTime),
          magazine(magazineCapacity, remainingBullets), fileTextureRectWeaponSize(texRectWeapon) {

}

Weapon::Magazine::Magazine(int magazineCapacity, int remainingBullets) : totalCapacity(magazineCapacity),
                                                                         remainingBullets(remainingBullets) {
}
