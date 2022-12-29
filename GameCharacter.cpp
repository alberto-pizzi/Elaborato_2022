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

void GameCharacter::chase(GameCharacter &enemy) {

}

bool GameCharacter::isLegalFight(const GameCharacter &enemy) const {
    return false;
}

GameCharacter::GameCharacter(const sf::Texture &tex, int hp, float speed, unsigned int points,
                             const sf::Vector2i &tilePosition,
                             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, std::string characterName,
                             bool animated,
                             unsigned int coins, int armor, bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex), fileTextureRectSkinSize(rectSkin) {

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

int GameCharacter::getHp() const {
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

void GameCharacter::setHp(int hp) {
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

void GameCharacter::enemySkinDirection(const sf::Vector2f &target) {
    //set Cartesian plane as enemy position
    sf::Vector2f origin = spriteCenter;
    sf::Vector2f translation = target - origin;
    float frameDuration = 0.5f;

    //when target exceeds bisects (+- 45°) of all quadrants, enemy changes body direction
    if (target.x >= origin.x) {
        if ((translation.y < translation.x) && (translation.y > -(translation.x))) {
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
        } else if (target.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
        } else if (target.y < origin.y) {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
        }
    } else if (target.x < origin.x) {
        if ((translation.y > translation.x) && (translation.y < -(translation.x))) {
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
        } else if (target.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
        } else {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
        }
    }

}

GameCharacter::~GameCharacter() = default;

