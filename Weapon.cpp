//
// Created by alber on 10/12/2022.
//

#include "Weapon.h"
#include "ArenaMap.h"

bool Weapon::reloadWeapon() {
    int bulletsForFillMagazine;
    float frameDuration = this->reloadTime;

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
            totalBullets -= bulletsForFillMagazine;
        }
        return true;
    } else
        return false;
}

Weapon::Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, sf::Time shotDelay,
               float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
               std::string weaponName, bool infiniteBullets)
        : equipped(equipped), totalBullets(totBullets), damage(damage), nextShotDelay(shotDelay),
          reloadTime(reloadTime),
          magazine(magazineCapacity, remainingBullets), fileTextureRectWeaponSize(texRectWeapon),
          weaponName(weaponName), weaponTexture(weaponTexture), infiniteBullets(infiniteBullets),
          defaultDamage(damage) {

    this->weaponSprite.setTexture(this->weaponTexture);

}

Weapon::~Weapon() {
    this->equipped = false;
}

void Weapon::drawWeapon(sf::RenderWindow &window) {
    sf::IntRect tmp = currentAnimation.getCurrentRect();
    if (this->isCut)
        tmp.width = this->cutValueX;
    else
        tmp.width = currentAnimation.getOriginalAnimationSizeX();
    //weaponSprite.setTextureRect(currentAnimation.getCurrentRect());
    weaponSprite.setTextureRect(tmp);
    window.draw(weaponSprite);
    //window.draw(hitBox);
}

bool Weapon::thereAreRemainingBullets() const {
    if (magazine.remainingBullets > 0)
        return true;
    else
        return false;
}

int Weapon::getTotalBullets() const {
    return totalBullets;
}

bool Weapon::isInfiniteBullets() const {
    return infiniteBullets;
}

const Weapon::Magazine &Weapon::getMagazine() const {
    return magazine;
}

const std::string &Weapon::getWeaponName() const {
    return weaponName;
}

float Weapon::getDegrees() const {
    return degrees;
}

void Weapon::setDegrees(float degrees) {
    Weapon::degrees = degrees;
}

const std::vector<std::unique_ptr<Bullet>> &Weapon::getBullets() const {
    return bullets;
}

void Weapon::drawBullets(sf::RenderWindow &window, float dt) const {
    for (int i = 0; i < bullets.size(); i++) {
        window.draw(bullets[i]->getBulletSprite());
        bullets[i]->move(bullets[i]->getBulletDir(), dt);
    }
}

const sf::Vector2i &Weapon::getFileTextureRectWeaponSize() const {
    return fileTextureRectWeaponSize;
}

void Weapon::updateBullets(ArenaMap *map, const sf::FloatRect &enemyBox) {
    for (int i = 0; i < bullets.size(); i++) {
        if ((map->collidesWithSolidsOrBounds(bullets[i]->getBulletSprite().getGlobalBounds())) ||
            bullets[i]->getBulletSprite().getGlobalBounds().intersects(enemyBox)) { //FIXME
            bullets.erase(bullets.begin() + i);
            i--;
            if (bullets.empty())
                break;
            continue;
        }
    }
}

void Weapon::setTotalBullets(int totalBullets) {
    Weapon::totalBullets = totalBullets;
}

void Weapon::setMagazine(const int remainingBullets, const int totalCapacity) {
    this->magazine.remainingBullets = remainingBullets;
    this->magazine.totalCapacity = totalCapacity;
}

bool Weapon::isEquipped() const {
    return equipped;
}

void Weapon::setEquipped(bool equipped) {
    Weapon::equipped = equipped;
}

const sf::Time &Weapon::getNextShotDelay() const {
    return nextShotDelay;
}

int Weapon::getDamage() const {
    return damage;
}

float Weapon::getDamageMultiplier() const {
    return damageMultiplier;
}

void Weapon::setDamageMultiplier(float damageMultiplier) {
    this->damageMultiplier = damageMultiplier;
}

int Weapon::getDefaultDamage() const {
    return defaultDamage;
}

void Weapon::setDamage(int damage) {
    this->damage = damage;
}


Weapon::Magazine::Magazine(int magazineCapacity, int remainingBullets) : totalCapacity(magazineCapacity),
                                                                         remainingBullets(remainingBullets) {
}
