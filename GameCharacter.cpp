//
// Created by alber on 18/10/2022.
//

#include "GameCharacter.h"


void GameCharacter::receiveDamage(float damagePoints) {
    if (!bubble) {
        if (armor > 0) {
            damagePoints = damageWithArmor(damagePoints);
            armor--;
        }
        HP -= damagePoints;
    }
}

sf::Vector2f GameCharacter::normalize(sf::Vector2f vector) const {
    auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
    //Prevent division by zero
    if (norm == 0)
        return sf::Vector2f{};
    else
        return vector / norm;
}

bool GameCharacter::isLegalFight(const GameCharacter &enemy) const {
    return false;
}

GameCharacter::GameCharacter(const sf::Texture &tex, float hp, float speed, unsigned int points,
                             const sf::Vector2i &tilePosition,
                             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType,
                             sf::Vector2f damageHit,
                             float hitRange, bool animated, unsigned int coins, int armor, bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex), fileTextureRectSkinSize(rectSkin), characterType(characterType),
          damageHit(damageHit) {

    sprite.setTexture(texture);

    //mike's frame position (in pixel)
    idle.reserve(1);
    idle = {
            {0 * fileTextureRectSkinSize.x, 0 * fileTextureRectSkinSize.y, fileTextureRectSkinSize.x,
             fileTextureRectSkinSize.y},
    };

    death.reserve(deathFrames);
    for (int i = 0; i < deathFrames; i++) {
        death.emplace_back(i * fileTextureRectSkinSize.x, 4 * fileTextureRectSkinSize.y, fileTextureRectSkinSize.x,
                           fileTextureRectSkinSize.y);
    }

    if (animated)
        sprite.setTextureRect(currentAnimation.getCurrentRect());
    else
        sprite.setTextureRect({0, 0, fileTextureRectSkinSize.x, fileTextureRectSkinSize.y});

    sprite.setPosition(sf::Vector2f(static_cast<float>(tilePosition.x * tileSize.x),
                                    static_cast<float>(tilePosition.y * tileSize.y)));

    updateGlobalPosition(sprite.getGlobalBounds()); //this updates coordinates in PosEntity

}


const sf::Sprite &GameCharacter::getSprite() const {
    return sprite;
}

float GameCharacter::getHp() const {
    return HP;
}

int GameCharacter::getArmor() const {
    return armor;
}

bool GameCharacter::isBubble() const {
    return bubble;
}

int GameCharacter::getPoints() const {
    return points;
}

int GameCharacter::getCoins() const {
    return coins;
}

void GameCharacter::setHp(float hp) {
    HP = hp;
}

void GameCharacter::setArmor(int armor) {
    GameCharacter::armor = armor;
}

void GameCharacter::setSpeed(float speed) {
    GameCharacter::speed = speed;
}

void GameCharacter::setBubble(bool bubble) {
    GameCharacter::bubble = bubble;
}

void GameCharacter::setPoints(int points) {
    GameCharacter::points = points;
}

void GameCharacter::setCoins(int coins) {
    GameCharacter::coins = coins;
}

int GameCharacter::getSpeed() const {
    return speed;
}

const std::vector<sf::IntRect> &GameCharacter::getGoRight() const {
    return goRight;
}

const std::vector<sf::IntRect> &GameCharacter::getGoLeft() const {
    return goLeft;
}

const std::vector<sf::IntRect> &GameCharacter::getGoDown() const {
    return goDown;
}

const std::vector<sf::IntRect> &GameCharacter::getGoUp() const {
    return goUp;
}

void GameCharacter::setSpritePos(sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}

float GameCharacter::damageWithArmor(float damagePoints) const {
    if (armor > 15)
        damagePoints /= 3;
    else if (armor > 10)
        damagePoints /= 2;
    else if (armor >= 5)
        damagePoints -= 2;

    if (damagePoints <= 0)
        damagePoints = 1;

    return damagePoints;
}

void GameCharacter::drawEntity(sf::RenderWindow &window, bool gameOver) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}

void GameCharacter::updateCharacterColor() {
    if (isHit) {
        sprite.setColor(hitColor);
        if (hitColorClock.getElapsedTime() >= hitTimeColor)
            isHit = false;
    } else if (bubble) {
        sprite.setColor(bubbleColor);
        if (weapon != nullptr)
            weapon->weaponSprite.setColor(bubbleColor);
    } else {
        sprite.setColor(sf::Color::White);
        if (weapon != nullptr)
            weapon->weaponSprite.setColor(sf::Color::White);
    }
}

void GameCharacter::characterSkinDirection(const sf::Vector2f &targetPos) {
    //set Cartesian plane as player position
    sf::Vector2f origin = spriteCenter;
    sf::Vector2f translation = targetPos - origin;
    float frameDuration = 0.5f;
    float radians, degrees;

    if (weapon != nullptr) {
        //weapon angle from input
        radians = std::atan(translation.y / translation.x);
        degrees = radians * static_cast<float>(180 / M_PI);
    }

    //when mouse exceeds bisects (+- 45°) of all quadrants, character changes body direction
    if (targetPos.x >= origin.x) {
        if (weapon != nullptr)
            weapon->weaponSprite.setScale(sf::Vector2f(1, 1));
        if ((translation.y < translation.x) && (translation.y > -(translation.x))) {
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = true;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        } else if (targetPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = true;
        } else if (targetPos.y < origin.y) {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            skinDirection[UP] = true;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        }
    } else if (targetPos.x < origin.x) {
        if (weapon != nullptr)
            weapon->weaponSprite.setScale(sf::Vector2f(-1, 1));
        if ((translation.y > translation.x) && (translation.y < -(translation.x))) {
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = true;
            skinDirection[DOWN] = false;
        } else if (targetPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = true;
        } else {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            skinDirection[UP] = true;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        }
    }

    if (weapon != nullptr) {
        if (weapon->getWeaponName() == "handgun")
            weapon->weaponSprite.setOrigin(sf::Vector2f(0, 0));
        else if (weapon->getWeaponName() == "assaultRifle")
            weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));
        else if (weapon->getWeaponName() == "shotgun")
            weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));

        weapon->weaponSprite.setRotation(degrees);
        weapon->setDegrees(degrees);

        //hit box
        weapon->hitBox.setScale(weapon->weaponSprite.getScale());
        weapon->hitBox.setRotation(degrees);
    }
}

bool GameCharacter::isHit1() const {
    return isHit;
}

void GameCharacter::setIsHit(bool isHit) {
    GameCharacter::isHit = isHit;
}

void GameCharacter::move(const sf::Vector2f &offset, float dt) {
    float newSpeed = this->speed;
    sf::Vector2f effectiveOffset;


    //set diagonal speed
    if (((offset.y > 0) && (offset.x > 0)) || ((offset.y > 0) && (offset.x < 0)) ||
        ((offset.y < 0) && (offset.x > 0)) || ((offset.y < 0) && (offset.x < 0)))
        newSpeed /= std::sqrt(2.f);

    effectiveOffset = offset * newSpeed * dt;
    sprite.setPosition(sprite.getPosition() + effectiveOffset);
    //pos = sprite.getGlobalBounds();
    updateGlobalPosition(sprite.getGlobalBounds());
    if ((effectiveOffset.x != 0) || (effectiveOffset.y != 0))
        currentAnimation.update(dt);
}

bool GameCharacter::isDead() const {
    if (HP <= 0)
        return true;
    else
        return false;
}

int GameCharacter::getCharacterType() const {
    return characterType;
}

void GameCharacter::hit(GameCharacter &target) {
    target.setIsHit(true);
    target.receiveDamage(static_cast<float>(randomDice.casualNumber(static_cast<int>(this->getDamageHit().x),
                                                                    static_cast<int>(this->getDamageHit().y))));
    target.hitColorClock.restart();
}


const sf::Vector2f &GameCharacter::getDamageHit() const {
    return damageHit;
}

GameCharacter::~GameCharacter() = default;

sf::FloatRect GameCharacter::futureCharacterPosition(const sf::Vector2f &offset, float dt) {
    float newSpeed = this->speed;
    sf::Vector2f effectiveOffset;


    //set diagonal speed
    if (((offset.y > 0) && (offset.x > 0)) || ((offset.y > 0) && (offset.x < 0)) ||
        ((offset.y < 0) && (offset.x > 0)) || ((offset.y < 0) && (offset.x < 0)))
        newSpeed /= std::sqrt(2.f);

    effectiveOffset = offset * newSpeed * dt;

    return {sprite.getGlobalBounds().left + effectiveOffset.x, sprite.getGlobalBounds().top + effectiveOffset.y,
            sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};

}

void GameCharacter::calculateDirectionVector() {

    if ((keyStates[LEFT] && keyStates[RIGHT]) || (!keyStates[LEFT] && !keyStates[RIGHT]))
        direction_vector.x = 0.f;
    else if (keyStates[LEFT])
        direction_vector.x = -1.f;
    else if (keyStates[RIGHT])
        direction_vector.x = 1.f;
    if ((keyStates[UP] && keyStates[DOWN]) || (!keyStates[UP] && !keyStates[DOWN]))
        direction_vector.y = 0.f;
    else if (keyStates[UP])
        direction_vector.y = -1.f;
    else if (keyStates[DOWN])
        direction_vector.y = 1.f;

}

void GameCharacter::calculateEnemyMoveDirectionArray(sf::Vector2f offset) {
    for (int i = 0; i < 4; i++) //set no input in all keyStates
        keyStates[i] = false;

    if (offset.y < 0)
        keyStates[UP] = true;

    if (offset.y >= 0)
        keyStates[DOWN] = true;

    if (offset.x < 0)
        keyStates[LEFT] = true;

    if (offset.x >= 0)
        keyStates[RIGHT] = true;

}

const std::vector<sf::IntRect> &GameCharacter::getDeath() const {
    return death;
}

void GameCharacter::startDespawning() {
    if (!despawnStarted) {
        currentAnimation.setNotCyclicalAnimation(death, 1.0f);
        despawnStarted = true;
    }
}

const sf::Color &GameCharacter::getHitColor() const {
    return hitColor;
}

void GameCharacter::setWeaponPosToShouldersPos() {
    if (currentAnimation.frames == goRight)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[RIGHT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[RIGHT].y);
    else if (currentAnimation.frames == goLeft)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width +
                                         weapon->startCenterForTranslation[LEFT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[LEFT].y);
    else if (currentAnimation.frames == goUp)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[UP].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[UP].y);
    else if (currentAnimation.frames == goDown)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[DOWN].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[DOWN].y);

    weapon->hitBox.setPosition(weapon->weaponSprite.getPosition());
}

