//
// Created by alber on 12/11/2022.
//

#include "Bonus.h"

#include <utility>

void Bonus::addPoints(GameCharacter &target) const {
    target.setPoints(target.getPoints() + bonusPoints);
}

Bonus::Bonus(const sf::Texture &texture, int points, sf::Time stayTime, sf::Vector2f spawnCoords,
             const std::vector<sf::IntRect> &animationFrames, int bonusType, sf::Vector2i frameSize,
             int textureRowIndex,
             bool isInfinite, bool ownable, bool hasDespawnAnimation)
        : bonusPoints(points), stayTime(stayTime), texture(texture), animationFrames(std::move(animationFrames)),
          bonusType(bonusType), isInfiniteAnimation(isInfinite), isOwnable(ownable), bonusFrameSize(frameSize),
          hasDespawnAnimation(hasDespawnAnimation) {
    //load sounds
    loadSounds();

    sprite.setTexture(texture);
    sprite.setPosition(spawnCoords);
    //updateGlobalPosition(sprite.getGlobalBounds());

    if (hasDespawnAnimation) { //bonuses with infinite animation (like coins) have a different animation comportment than the others


        despawnFrames.reserve(DESPAWN);
        for (int i = 0; i < DESPAWN; i++)
            despawnFrames.emplace_back(i * animationFrameSize.x, 1 * animationFrameSize.y, animationFrameSize.x,
                                       animationFrameSize.y);

        //these numbers are the sprite borders (translation pixels), they depend on your own texture
        idleBonusBox = {{(textureRowIndex * animationFrameSize.x) + 22, 2 * animationFrameSize.y + 24, 23, 25}};

        translation = {static_cast<float>(idleBonusBox[0].left % animationFrameSize.x),
                       static_cast<float>(idleBonusBox[0].top % animationFrameSize.y)};
        this->animationFrames = idleBonusBox;
        currentAnimation.idleFrames = idleBonusBox;

        this->sprite.setScale(sf::Vector2f(1.5, 1.5));

        //play spawn bonus sound
        audioManager.playSound("spawnBonus");
    }


    sprite.setTextureRect(currentAnimation.getCurrentRect());

    stayTimer.restart();
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

        //play destroy wooden box sound
        audioManager.playSound("destroyBox");
    }
}

const sf::Time &Bonus::getDuration() const {
    return duration;
}

void Bonus::loadSounds() {
    //despawn bonus (over time)
    audioManager.loadSound("destroyBox", "res/sounds/destroy_box.ogg");

    //spawn bonus
    audioManager.loadSound("spawnBonus", "res/sounds/spawn_bonus.ogg");
}


