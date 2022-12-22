//
// Created by alber on 12/11/2022.
//

#include "Bonus.h"

#include <utility>

void Bonus::addPoints(GameCharacter &target) const {
    target.setPoints(target.getPoints() + bonusPoints);
}

Bonus::Bonus(const sf::Texture &texture, int points, sf::Time stayTime, sf::Vector2f spawnCoords,
             std::vector<sf::IntRect> animationFrames, int bonusType, bool isInfinite)
        : bonusPoints(points), stayTime(stayTime), texture(texture), animationFrames(std::move(animationFrames)),
          bonusType(bonusType), isInfiniteAnimation(isInfinite) {
    this->sprite.setTexture(texture);
    this->sprite.setPosition(spawnCoords);
    //this->updateGlobalPosition(sprite.getGlobalBounds());

    sprite.setTextureRect(currentAnimation.getCurrentRect());
}

bool Bonus::isAbove(const sf::FloatRect &characterGlobalPos) const {
    if (characterGlobalPos.intersects(this->sprite.getGlobalBounds()))
        return true;
    else
        return false;
}

void Bonus::drawBonus(sf::RenderWindow &window) {
    this->sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(this->sprite);
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
}


