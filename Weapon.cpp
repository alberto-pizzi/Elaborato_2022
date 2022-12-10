//
// Created by alber on 10/12/2022.
//

#include "Weapon.h"

bool Weapon::reloadWeapon() {
    return false;
}

Weapon::Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, float shotDelay,
               float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
               std::string weaponName)
        : equipped(equipped), totalBullets(totBullets), damage(damage), nextShotDelay(shotDelay),
          reloadTime(reloadTime),
          magazine(magazineCapacity, remainingBullets), fileTextureRectWeaponSize(texRectWeapon),
          weaponName(weaponName), weaponTexture(weaponTexture) {

    this->weaponSprite.setTexture(this->weaponTexture);

    idleWeapon.reserve(1);
    idleWeapon = {
            {0 * this->fileTextureRectWeaponSize.x, 0 * this->fileTextureRectWeaponSize.y,
             this->fileTextureRectWeaponSize.x,
             this->fileTextureRectWeaponSize.y},
    };

    weaponSprite.setTextureRect({0, 0, 64, 32});
}

Weapon::~Weapon() {
    this->equipped = false;
}

void Weapon::drawWeapon(sf::RenderWindow &window) {
    window.draw(weaponSprite);
}

Weapon::Magazine::Magazine(int magazineCapacity, int remainingBullets) : totalCapacity(magazineCapacity),
                                                                         remainingBullets(remainingBullets) {
}
