//
// Created by alber on 10/12/2022.
//

#include "Weapon.h"

bool Weapon::reloadWeapon() {
    int bulletsForFillMagazine;
    float frameDuration = 1.0f;

    if (((infiniteBullets) || (totalBullets > 0)) && (magazine.remainingBullets != magazine.totalCapacity)) {
        currentAnimation.setNotCyclicalAnimation(reload, frameDuration);
        if (infiniteBullets)
            magazine.remainingBullets = magazine.totalCapacity;
        else {
            bulletsForFillMagazine = magazine.totalCapacity - magazine.remainingBullets;
            if (totalBullets >= bulletsForFillMagazine)
                magazine.remainingBullets += bulletsForFillMagazine;
            else
                magazine.remainingBullets += totalBullets;
        }
        return true;
    } else
        return false;
}

Weapon::Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, float shotDelay,
               float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
               std::string weaponName, bool infiniteBullets)
        : equipped(equipped), totalBullets(totBullets), damage(damage), nextShotDelay(shotDelay),
          reloadTime(reloadTime),
          magazine(magazineCapacity, remainingBullets), fileTextureRectWeaponSize(texRectWeapon),
          weaponName(weaponName), weaponTexture(weaponTexture), infiniteBullets(infiniteBullets) {

    this->weaponSprite.setTexture(this->weaponTexture);

}

Weapon::~Weapon() {
    this->equipped = false;
}

void Weapon::drawWeapon(sf::RenderWindow &window) {
    weaponSprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(weaponSprite);
}

bool Weapon::thereAreRemainingBullets() const {
    if (magazine.remainingBullets > 0)
        return true;
    else
        return false;
}

float Weapon::getNextShotDelay() const {
    return nextShotDelay;
}

Weapon::Magazine::Magazine(int magazineCapacity, int remainingBullets) : totalCapacity(magazineCapacity),
                                                                         remainingBullets(remainingBullets) {
}
