//
// Created by alber on 12/11/2022.
//

#include "Bonus.h"

#include <utility>

void Bonus::addPoints(GameCharacter &target) const {
    target.setPoints(target.getPoints() + bonusPoints);
}

Bonus::Bonus(const sf::Texture &texture, int points, sf::Time stayTime, sf::Vector2f spawnCoords,
             std::vector<sf::IntRect> animationFrames, int bonusType, sf::Vector2i frameSize, bool isInfinite,
             bool ownable)
        : bonusPoints(points), stayTime(stayTime), texture(texture), animationFrames(std::move(animationFrames)),
          bonusType(bonusType), isInfiniteAnimation(isInfinite), isOwnable(ownable), bonusFrameSize(frameSize) {
    sprite.setTexture(texture);
    sprite.setPosition(spawnCoords);
    //updateGlobalPosition(sprite.getGlobalBounds());

    if (bonusType != COINS) { //COINS has a different animation comportment than the others
        despawnFrames.reserve(DESPAWN);
        for (int i = 0; i < DESPAWN; i++)
            despawnFrames.emplace_back(i * frameSize.x, 1 * frameSize.y, frameSize.x, frameSize.y);
    }


    sprite.setTextureRect(currentAnimation.getCurrentRect());
}

bool Bonus::isAbove(const sf::FloatRect &characterGlobalPos) const {
    if (characterGlobalPos.intersects(sprite.getGlobalBounds()))
        return true;
    else
        return false;
}

void Bonus::drawBonus(sf::RenderWindow &window) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}

int Bonus::getBonusType() const {
    return bonusType;
}

const sf::Time &Bonus::getStayTime() const {
    return stayTime;
}

const sf::Clock &Bonus::getStayTimer() const {
    return stayTimer;
}

void Bonus::startDespawining() {
//WARNING: only for common animations
    if (!despawnStarted) {
        currentAnimation.setNotCyclicalAnimation(despawnFrames, 1.0f);
        sprite.setPosition(sprite.getPosition() - translation);
        despawnStarted = true;
    }
}

const sf::Time &Bonus::getDuration() const {
    return duration;
}


