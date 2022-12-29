//
// Created by alber on 18/10/2022.
//

#include "GameCharacter.h"


void GameCharacter::receiveDamage(int damagePoints) {
    if (!bubble) {
        if (armor > 0) {
            int armorDamage = armor - damagePoints;
            if (armorDamage >= 0)
                armor -= armorDamage;
            else {
                armor = 0;
                HP += armorDamage; //add damage because it is certainly negative
            }

        } else
            HP -= damagePoints;
    }
}

void GameCharacter::chase(const GameCharacter &target, float dt) {
    move(normalize(target.getSpriteCenter()), dt);
}

sf::Vector2f GameCharacter::normalize(sf::Vector2f vector) {
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

GameCharacter::GameCharacter(const sf::Texture &tex, int hp, float speed, unsigned int points,
                             const sf::Vector2i &tilePosition,
                             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType,
                             bool animated,
                             unsigned int coins, int armor, bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex), fileTextureRectSkinSize(rectSkin), characterType(characterType) {

    sprite.setTexture(texture);

    //mike's frame position (in pixel)
    idle.reserve(1);
    idle = {
            {0 * fileTextureRectSkinSize.x, 0 * fileTextureRectSkinSize.y, fileTextureRectSkinSize.x,
             fileTextureRectSkinSize.y},
    };
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

int GameCharacter::howMuchDamage() const {
    int damagePoints = weapon->getDamage(); //FIXME implement features for character without weapon (zombie...)
    if (armor > 15)
        damagePoints /= 3;
    else if (armor > 10)
        damagePoints /= 2;
    else if (armor >= 5)
        damagePoints -= 2;

    return damagePoints;
}

void GameCharacter::drawEntity(sf::RenderWindow &window) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}

void GameCharacter::updateCharacterColor() {
    if (bubble) {
        sprite.setColor(bubbleColor);
        weapon->weaponSprite.setColor(bubbleColor);
    }
        //TODO add here hit color
    else {
        sprite.setColor(sf::Color::White);
        weapon->weaponSprite.setColor(sf::Color::White);
    }
}

void GameCharacter::characterSkinDirection(const sf::Vector2f &targetPos) {
    //set Cartesian plane as player position
    sf::Vector2f origin = spriteCenter;
    sf::Vector2f translation = targetPos - origin;
    float frameDuration = 0.5f;
    float radians, degrees;


    //weapon angle from input
    radians = std::atan(translation.y / translation.x);
    degrees = radians * static_cast<float>(180 / M_PI);

    //when mouse exceeds bisects (+- 45°) of all quadrants, Mike changes body direction
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

GameCharacter::~GameCharacter() = default;

