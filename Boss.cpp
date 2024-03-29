//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Boss.h"

unsigned int Boss::roundCount = 1;

Boss::Boss(const sf::Texture &bossTexture, const sf::Texture &scepterTex, const sf::Texture &energyTex,
           const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin,
           sf::Vector2f damageHit, float hp, bool animated, float speed, unsigned int points, unsigned int coins,
           float armor) : GameCharacter(bossTexture, hp * (static_cast<float>(roundCount) / 2),
                                        speed,
                                        points,
                                        spawnTile,
                                        tileSize,
                                        rectSkin, BOSS, damageHit,
                                        animated,
                                        coins,
                                        armor) {
    this->sprite.setScale(scaleSize);
    roundCount++;
    spawnOrigin = getSpriteCenter();

    weapon = std::unique_ptr<Weapon>(
            new Scepter(true, scepterTex, energyTex, scaleSize, damageHit.y)); //max value of damage hit

    //load boss spawning sound
    audioManager.playSound("bossSpawning");

    bubbleClock.restart();
}

void Boss::updateCharacterColor() {
    if (bubble) {
        sprite.setColor(bubbleColor);
        if (weapon)
            weapon->weaponSprite.setColor(bubbleColor);
    } else if (isHit) {
        sprite.setColor(hitColor);
        if (weapon)
            weapon->weaponSprite.setColor(hitColor);
        if (hitColorClock.getElapsedTime() >= hitTime)
            isHit = false;
    } else {
        sprite.setColor(sf::Color::White);
        if (weapon)
            weapon->weaponSprite.setColor(sf::Color::White);
    }
}

void Boss::receiveDamage(float damagePoints) {
    if (!bubble) {
        if (armor > 0) {
            damagePoints = damageWithArmor(damagePoints);
            armor--;
        }
        HP -= damagePoints;
    }
}

float Boss::getMaxMovingRange() const {
    return maxMovingRange;
}

const sf::Vector2f &Boss::getSpawnOrigin() const {
    return spawnOrigin;
}

bool Boss::isBubble() const {
    return bubble;
}

void Boss::setBubble(bool bubble) {
    Boss::bubble = bubble;
    if (bubble)
        durationClock.restart();
    else
        bubbleClock.restart();
}

const sf::Time &Boss::getBubbleDuration() const {
    return bubbleDuration;
}

const sf::Time &Boss::getBubbleOffset() const {
    return bubbleOffset;
}

void Boss::bossBubble() {
    if (isBubble() &&
        (durationClock.getElapsedTime() >= getBubbleDuration()))
        setBubble(false);

    if (!isBubble() &&
        (bubbleClock.getElapsedTime() >= getBubbleOffset()))
        setBubble(true);
}
