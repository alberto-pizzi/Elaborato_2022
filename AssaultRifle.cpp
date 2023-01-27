//
// Created by alber on 12/12/2022.
//

#include "AssaultRifle.h"

void AssaultRifle::shoot(const sf::Vector2f &normalizedBulletDir) {

    float frameDuration = 0.35f;
    currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

    sf::Vector2f bulletScale = weaponSprite.getScale();

    //shoot ONE bullet
    bullets.emplace_back(new Bullet(bulletTexture, 1700, weaponSprite.getOrigin(), degrees,
                                    weaponSprite.getScale(), normalizedBulletDir, weaponSprite.getPosition(),
                                    barrelHole, bulletScale));

    //load sound effect
    audioManager.playSound("rifleShot");

    shotClock.restart();
    magazine.remainingBullets--;
}

AssaultRifle::AssaultRifle(bool equipped, const sf::Texture &handgunTexture,
                           const sf::Texture &assaultRifleBulletTexture,
                           int totBullets, int damage, sf::Time shotDelay, float reloadTime, int magazineCapacity,
                           int remainingBullets) : Weapon(
        equipped,
        handgunTexture,
        totBullets,
        damage,
        shotDelay,
        reloadTime,
        magazineCapacity,
        remainingBullets,
        fileTextureRectAssaultShotSize,
        "assaultRifle",
        false) {

    //these values are used to give the correct starting point for centering on the player's shoulder
    startCenterForTranslation[LEFT] = {-16, 21};
    startCenterForTranslation[RIGHT] = {16, 21};
    startCenterForTranslation[UP] = {32, 21};
    startCenterForTranslation[DOWN] = {24, 21};


    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, fileTextureRectAssaultShotSize.x, fileTextureRectAssaultShotSize.y},
    };

    weaponSprite.setTextureRect({0, 0, fileTextureRectAssaultShotSize.x, fileTextureRectAssaultShotSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * fileTextureRectAssaultShotSize.x, 0, fileTextureRectAssaultShotSize.x,
                          fileTextureRectAssaultShotSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * fileTextureRectAssaultReloadSize.x, 1 * fileTextureRectAssaultReloadSize.y,
                            fileTextureRectAssaultReloadSize.x,
                            fileTextureRectAssaultReloadSize.y);

    //these values are the hit box weapon size from texture file
    hitBox.setSize(sf::Vector2f(66, 30));

    //set bullet texture
    bulletTexture = assaultRifleBulletTexture;
}
