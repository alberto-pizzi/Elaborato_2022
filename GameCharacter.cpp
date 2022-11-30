//
// Created by alber on 18/10/2022.
//

#include "GameCharacter.h"

int GameCharacter::receiveDamage(int damagePoints, bool armor) {
    return 0;
}

void GameCharacter::chase(GameCharacter &enemy) {

}

bool GameCharacter::isLegalFight(const GameCharacter &enemy) const {
    return false;
}

GameCharacter::GameCharacter(const sf::Texture &tex, int hp, float speed, int points, const sf::Vector2i &tilePosition,
                             int coins,
                             int armor, bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex) {
    sprite.setTexture(texture);
    pos = {(static_cast<float>(tilePosition.x) * sprite.getGlobalBounds().width) + sprite.getGlobalBounds().width / 2,
           (static_cast<float>(tilePosition.y) * sprite.getGlobalBounds().height) +
           sprite.getGlobalBounds().height / 2};

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

GameCharacter::~GameCharacter() = default;

