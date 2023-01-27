//
// Created by alber on 13/12/2022.
//

#include "Shotgun.h"

void Shotgun::shoot(const sf::Vector2f &normalizedBulletDir) {
    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);
    float speed = 1500;
    float delta = deltaDegrees; //delta degrees

    sf::Vector2f newNormalizedDir1 = {normalizedBulletDir.x * static_cast<float>(std::cos((M_PI * (-delta)) / 180)) -
                                      normalizedBulletDir.y * static_cast<float>(std::sin((M_PI * (-delta)) / 180)),
                                      normalizedBulletDir.x * static_cast<float>(std::sin((M_PI * (-delta)) / 180)) +
                                      normalizedBulletDir.y * static_cast<float>(std::cos((M_PI * (-delta)) / 180))};
    sf::Vector2f newNormalizedDir3 = {normalizedBulletDir.x * static_cast<float>(std::cos((M_PI * (delta)) / 180)) -
                                      normalizedBulletDir.y * static_cast<float>(std::sin((M_PI * (delta)) / 180)),
                                      normalizedBulletDir.x * static_cast<float>(std::sin((M_PI * (delta)) / 180)) +
                                      normalizedBulletDir.y * static_cast<float>(std::cos((M_PI * (delta)) / 180))};

    //corrects west trajectory
    if (weaponSprite.getScale().x < 0) {
        sf::Vector2f tmpNewNormalizedDir = newNormalizedDir1;
        newNormalizedDir1 = newNormalizedDir3;
        newNormalizedDir3 = tmpNewNormalizedDir;
    }

    //shoot THREE bullets
    bullets.emplace_back(new ShotgunBullet(bulletTexture, speed, barrelHole, weaponSprite.getPosition(),
                                           degrees, weaponSprite.getOrigin(),
                                           weaponSprite.getScale(), newNormalizedDir1, 1));
    bullets.emplace_back(new ShotgunBullet(bulletTexture, speed, barrelHole, weaponSprite.getPosition(),
                                           degrees, weaponSprite.getOrigin(),
                                           weaponSprite.getScale(), normalizedBulletDir, 2));
    bullets.emplace_back(new ShotgunBullet(bulletTexture, speed, barrelHole, weaponSprite.getPosition(),
                                           degrees, weaponSprite.getOrigin(),
                                           weaponSprite.getScale(), newNormalizedDir3, 3));

    //play audio effect
    audioManager.playSound("shotgunShot");

    shotClock.restart();

    magazine.remainingBullets--; //three bullets are counted as one shot
}

Shotgun::Shotgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &shotgunBulletTexture,
                 int totBullets,
                 int damage, sf::Time shotDelay, float reloadTime, int magazineCapacity, int remainingBullets) : Weapon(
        equipped,
        handgunTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectShotgunShotSize,
        "shotgun",
        false) {

    //these values are used to give the correct starting point for centering on the player's shoulder
    startCenterForTranslation[LEFT] = {-16, 27};
    startCenterForTranslation[RIGHT] = {16, 27};
    startCenterForTranslation[UP] = {32, 27};
    startCenterForTranslation[DOWN] = {24, 27};

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, fileTextureRectShotgunShotSize.x, fileTextureRectShotgunShotSize.y},
    };

    weaponSprite.setTextureRect({0, 0, fileTextureRectShotgunShotSize.x, fileTextureRectShotgunShotSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * fileTextureRectShotgunShotSize.x, 0, fileTextureRectShotgunShotSize.x,
                          fileTextureRectShotgunShotSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * fileTextureRectShotgunReloadSize.x, 2 * fileTextureRectShotgunReloadSize.y,
                            fileTextureRectShotgunReloadSize.x,
                            fileTextureRectShotgunReloadSize.y);

    //these values are the hit box weapon size from texture file
    hitBox.setSize(sf::Vector2f(70, 15));

    //set bullet texture
    bulletTexture = shotgunBulletTexture;

}

void Shotgun::updateBullets(ArenaMap *map, GameCharacter &enemy) {
    Weapon::updateBullets(map, enemy);
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getDistanceTravelled() >= bulletRange) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
        if (bullets.empty()) //if you make changes, it must be after each vector erase
            break;
    }
}

bool Shotgun::reloadWeapon() {
    int bulletsForFillMagazine;
    float frameDuration = this->reloadTime;

    if (((infiniteBullets) || (totalBullets > 0)) && (magazine.remainingBullets != magazine.totalCapacity)) {
        if (!reload.empty())
            currentAnimation.setNotCyclicalAnimation(reload, frameDuration);
        if (infiniteBullets)
            magazine.remainingBullets = magazine.totalCapacity;
        else {
            magazine.remainingBullets++;
            totalBullets--;
        }
        //shotgun reload sound
        audioManager.playSound("bulletInsert");
        return true;
    } else
        return false;

}
