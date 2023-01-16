//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Kamikaze.h"

Kamikaze::Kamikaze(const sf::Texture &kamikazeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
                   const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
                   bool animated, int hp, float speed, unsigned int points, unsigned int coins, int armor, bool bubble)
        : Enemy(kamikazeTexture, hp, speed, points,
                spawnTile,
                tileSize, rectSkin, KAMIKAZE, damageHit, nodeMap, 100,
                3,
                animated,
                coins, armor, bubble) {
    this->sprite.setScale(sf::Vector2f(1.5, 1.5));
    //WARNING: work here to edit frames
    goDown.reserve(3);
    goDown = {
            {0 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goLeft.reserve(3);
    goLeft = {
            {0 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goRight.reserve(3);
    goRight = {
            {0 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goUp.reserve(3);
    goUp = {
            {0 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    //FIXME
    explosionArea.setRadius(56);
    explosionArea.setFillColor(sf::Color::Blue);
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

bool Kamikaze::isAbleToHit(const GameCharacter &target, const Dice &hitDice) {
    if (target.getSprite().getGlobalBounds().intersects(explosionArea.getGlobalBounds()))
        return true;
    else
        return false;
}

void Kamikaze::hit(GameCharacter &target) {

}

void Kamikaze::areaHit(std::vector<std::unique_ptr<Enemy>> &targets) {
    if (!explosionStarted) {
        explosionStarted = true;
        explosionClock.restart();
        std::cout << "START EXPLOSION COUNT" << std::endl;
    }
    //kamikaze explosion
    if (explosionStarted && (explosionClock.getElapsedTime() >= explosionTime)) {
        Dice tmpDice;
        for (int j = 0; j < targets.size(); j++) {
            if (this->isAbleToHit(*(targets[j]), tmpDice)) { //FIXME hitchance
                targets[j]->setIsHit(true);
                targets[j]->hitColorClock.restart();
                targets[j]->receiveDamage(
                        static_cast<float>(randomDice.casualNumber(static_cast<int>(this->getDamageHit().x),
                                                                   static_cast<int>(this->getDamageHit().y))));
            }
        }
        std::cout << "KABOOM" << std::endl;
        this->HP = 0; //kill himself
        explosionStarted = false;
    }
}
