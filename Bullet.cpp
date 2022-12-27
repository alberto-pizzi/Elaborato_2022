//
// Created by alber on 18/12/2022.
//

#include "Bullet.h"

Bullet::Bullet(const sf::Texture &tex, float speed, const sf::Vector2f &rotationOrigin, float degrees,
               const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir) : bulletSpeed(speed), bulletTexture(tex),
                                                                                 bulletDir(bulletDir) {

    bulletSprite.setTexture(tex);
    bulletSprite.setScale(weaponScale);
    bulletSprite.setRotation(degrees);
}

bool Bullet::checkEnemyCollision(const GameCharacter &target) {
    return false;
}

const sf::Sprite &Bullet::getBulletSprite() const {
    return bulletSprite;
}

const sf::Texture &Bullet::getBulletTexture() const {
    return bulletTexture;
}

void Bullet::setBulletTexture(const sf::Texture &bulletTexture) {
    Bullet::bulletTexture = bulletTexture;
}

const sf::Vector2f &Bullet::getBulletDir() const {
    return bulletDir;
}

void Bullet::move(const sf::Vector2f &offset, float dt) {
    sf::Vector2f currentVelocity = offset * dt * bulletSpeed;
    bulletSprite.setPosition(bulletSprite.getPosition() + currentVelocity);
    updateGlobalPosition(bulletSprite.getGlobalBounds());
}

float Bullet::getBulletSpeed() const {
    return bulletSpeed;
}
