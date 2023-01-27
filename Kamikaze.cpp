//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Kamikaze.h"

Kamikaze::Kamikaze(const sf::Texture &kamikazeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
                   const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
                   bool animated, int hp, float speed, unsigned int points, unsigned int coins, float armor)
        : Enemy(kamikazeTexture, hp, speed, points,
                spawnTile,
                tileSize, rectSkin, KAMIKAZE, damageHit, nodeMap, 100,
                3,
                animated,
                coins, armor) {


    explosionArea.setRadius(explosionRadius);
    explosionArea.setPosition(getSpriteCenter().x - explosionArea.getRadius(),
                              getSpriteCenter().y - explosionArea.getRadius());

}

const sf::Clock &Kamikaze::getExplosionClock() const {
    return explosionClock;
}

void Kamikaze::setExplosionClock(const sf::Clock &explosionClock) {
    Kamikaze::explosionClock = explosionClock;
}

const sf::Time &Kamikaze::getExplosionTime() const {
    return explosionTime;
}

void Kamikaze::setExplosionTime(const sf::Time &explosionTime) {
    Kamikaze::explosionTime = explosionTime;
}

bool Kamikaze::isExplosionStarted() const {
    return explosionStarted;
}

void Kamikaze::setExplosionStarted(bool explosionStarted) {
    Kamikaze::explosionStarted = explosionStarted;
}

void Kamikaze::drawEntity(sf::RenderWindow &window, bool gameOver) {
    explosionArea.setPosition(getSpriteCenter().x - explosionArea.getRadius(),
                              getSpriteCenter().y - explosionArea.getRadius());
    //window.draw(explosionArea);
    GameCharacter::drawEntity(window, gameOver);
}

bool Kamikaze::isAbleToHit(const GameCharacter &target, const Dice &hitDice, float hitChance) {
    if (target.getSprite().getGlobalBounds().intersects(explosionArea.getGlobalBounds()))
        return true;
    else
        return false;
}

void Kamikaze::hit(GameCharacter &target, std::vector<std::unique_ptr<Enemy>> &targetEnemies) {
    if (!explosionStarted) {
        explosionStarted = true;
        explosionClock.restart();
        std::cout << "START EXPLOSION COUNT" << std::endl;
    }

    //kamikaze explosion
    if (explosionStarted && (explosionClock.getElapsedTime() >= explosionTime)) {
        Dice tmpDice;
        for (int j = 0; j < targetEnemies.size(); j++) {
            if (this->isAbleToHit(*(targetEnemies[j]), tmpDice, 1)) {
                targetEnemies[j]->setIsHit(true);
                targetEnemies[j]->hitColorClock.restart();
                targetEnemies[j]->receiveDamage(
                        static_cast<float>(randomDice.casualNumber(static_cast<int>(this->getDamageHit().x),
                                                                   static_cast<int>(this->getDamageHit().y))));
            }
        }

        //hit target (mike)
        if (this->isAbleToHit(target, tmpDice, 1))
            Enemy::hit(target, targetEnemies);

        //expand sprite for explosion
        sprite.setScale(sprite.getScale() * 2.f);

        //kill himself
        this->HP = 0;
        explosionStarted = false;
    }
}

