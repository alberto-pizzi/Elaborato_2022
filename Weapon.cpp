//
// Created by alber on 10/12/2022.
//

#include "Weapon.h"
#include "ArenaMap.h"

bool Weapon::reloadWeapon() {
    int bulletsForFillMagazine;
    float frameDuration = this->reloadTime;

    if (((infiniteBullets) || (totalBullets > 0)) && (magazine.remainingBullets != magazine.totalCapacity)) {
        if (!reload.empty())
            currentAnimation.setNotCyclicalAnimation(reload, frameDuration);
        if (infiniteBullets)
            magazine.remainingBullets = magazine.totalCapacity;
        else {
            bulletsForFillMagazine = magazine.totalCapacity - magazine.remainingBullets;
            if (totalBullets >= bulletsForFillMagazine) {
                magazine.remainingBullets += bulletsForFillMagazine;
                totalBullets -= bulletsForFillMagazine;
            } else {
                magazine.remainingBullets += totalBullets;
                totalBullets = 0;
            }
        }
        //reload sound
        audioManager.playSound("reloadMagazine");

        return true;
    } else
        return false;
}

Weapon::Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, float damage, sf::Time shotDelay,
               float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
               std::string weaponName, bool infiniteBullets)
        : equipped(equipped), totalBullets(totBullets), damage(damage), nextShotDelay(shotDelay),
          reloadTime(reloadTime),
          magazine(magazineCapacity, remainingBullets), fileTextureRectWeaponSize(texRectWeapon),
          weaponName(weaponName), weaponTexture(weaponTexture), infiniteBullets(infiniteBullets),
          defaultDamage(damage) {

    //load sounds
    loadSounds();

    this->weaponSprite.setTexture(this->weaponTexture);

    //play the weapon picked up sound
    playWeaponPickedUpSound();
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
    //window.draw(hitBox);
    window.draw(weaponSprite);
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

void Weapon::updateBullets(ArenaMap *map, GameCharacter &enemy) {
    for (int i = 0; i < bullets.size(); i++) {
        if (map->collidesWithSolidsOrBounds(bullets[i]->getBulletSprite().getGlobalBounds())) { //FIXME
            bullets.erase(bullets.begin() + i);
            i--;
        } else if (bullets[i]->getBulletSprite().getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds())) {
            enemy.setIsHit(true);
            enemy.hitColorClock.restart();
            enemy.receiveDamage(this->damage);

            bullets.erase(bullets.begin() + i);
            i--;
        }
        if (bullets.empty()) //if you make changes, it must be after each vector erase
            break;
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

float Weapon::getDamage() const {
    return damage;
}

float Weapon::getDamageMultiplier() const {
    return damageMultiplier;
}

void Weapon::setDamageMultiplier(float damageMultiplier) {
    this->damageMultiplier = damageMultiplier;
}

float Weapon::getDefaultDamage() const {
    return defaultDamage;
}

void Weapon::setDamage(float damage) {
    this->damage = damage;
}

void Weapon::loadSounds() {
    //magazine weapon
    audioManager.loadSound("reloadMagazine", "res/sounds/magazine_in.ogg");

    //handgun
    audioManager.loadSound("handgunClick", "res/sounds/handgun_click.ogg");
    audioManager.loadSound("handgunShot", "res/sounds/handgun_shot.ogg");

    //assault rifle
    audioManager.loadSound("rifleClick", "res/sounds/rifle_click.ogg");
    audioManager.loadSound("rifleShot", "res/sounds/rifle_shot.ogg");

    //shotgun
    audioManager.loadSound("shotgunClick", "res/sounds/shotgun_click.ogg");
    audioManager.loadSound("shotgunShot", "res/sounds/shotgun_shot.ogg");
    audioManager.loadSound("bulletInsert", "res/sounds/bullet_insert.ogg");

    //bow
    audioManager.loadSound("bowShot", "res/sounds/bow_shot.ogg");

    //scepter
    audioManager.loadSound("scepterShot", "res/sounds/scepter_shot.ogg");
}

void Weapon::playWeaponPickedUpSound() {
    if (equipped) {
        if (weaponName == "handgun")
            audioManager.playSound("handgunClick");
        else if (weaponName == "assaultRifle")
            audioManager.playSound("rifleClick");
        else if (weaponName == "shotgun")
            audioManager.playSound("shotgunClick");
    }
}


Weapon::Magazine::Magazine(int magazineCapacity, int remainingBullets) : totalCapacity(magazineCapacity),
                                                                         remainingBullets(remainingBullets) {
}
