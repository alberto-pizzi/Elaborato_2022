//
// Created by alber on 10/12/2022.
//

#include "Handgun.h"

void Handgun::shoot(const sf::Vector2f &normalizedBulletDir) {
    if (shotClock.getElapsedTime() >= nextShotDelay) {
        if (thereAreRemainingBullets()) {
            float frameDuration = 0.35f;
            currentAnimation.setNotCyclicalAnimation(shot, frameDuration);

            sf::Vector2f bulletScale = weaponSprite.getScale();

            //shoot ONE bullet
            bullets.emplace_back(new Bullet(bulletTexture, 1200, weaponSprite.getOrigin(), degrees,
                                            weaponSprite.getScale(), normalizedBulletDir, weaponSprite.getPosition(),
                                            barrelHole, bulletScale));
            //play audio effect
            audioManager.playSound("handgunShot");

            shotClock.restart();
            magazine.remainingBullets--;
            animationKeyStep[ReloadingAnimationKeySteps::ACTIVE] = true;
        } else
            //play gun dry sound
            audioManager.playSound("gunDry");
    }
}

Handgun::Handgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
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
        fileTextureRectHandgunSize,
        "handgun",
        true) {
    //these values are used to give the correct starting point for centering on the player's shoulder
    startCenterForTranslation[LEFT] = {-16, 21};
    startCenterForTranslation[RIGHT] = {16, 21};
    startCenterForTranslation[UP] = {32, 21};
    startCenterForTranslation[DOWN] = {24, 21};

    idleWeapon.reserve(IDLE);
    idleWeapon = {
            {0, 0, fileTextureRectHandgunSize.x, fileTextureRectHandgunSize.y},
    };

    weaponSprite.setTextureRect({0, 0, fileTextureRectHandgunSize.x, fileTextureRectHandgunSize.y});

    shot.reserve(SHOT);
    for (int i = 0; i < SHOT; i++)
        shot.emplace_back(i * fileTextureRectHandgunSize.x, 0, fileTextureRectHandgunSize.x,
                          fileTextureRectHandgunSize.y);

    reload.reserve(RELOAD);
    for (int i = 0; i < RELOAD; i++)
        reload.emplace_back(i * fileTextureRectHandgunSize.x, 1 * fileTextureRectHandgunSize.y,
                            fileTextureRectHandgunSize.x,
                            fileTextureRectHandgunSize.y);

    //these values are the hit box weapon size from texture file
    hitBox.setSize(sf::Vector2f(40, 20));

    //set bullet texture
    bulletTexture = handgunBulletTexture;
}
