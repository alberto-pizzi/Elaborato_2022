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
                             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, bool animated, int coins,
                             int armor,
                             bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex), fileTextureRectSkinSize(rectSkin) {

    sprite.setTexture(texture);

    //mike's frame position (in pixel)
    idle.reserve(1);
    idle = {
            {0 * this->fileTextureRectSkinSize.x, 0 * this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x,
             this->fileTextureRectSkinSize.y},
    };
    if (animated)
        sprite.setTextureRect(currentAnimation.getCurrentRect());
    else
        sprite.setTextureRect({0, 0, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y});

    sf::Vector2f spriteCenter = {static_cast<float>(sprite.getTextureRect().width) / 2,
                                 static_cast<float>(sprite.getTextureRect().height) / 2};

    sprite.setPosition(sf::Vector2f(static_cast<float>(tilePosition.x * tileSize.x),
                                    static_cast<float>(tilePosition.y * tileSize.y)));

    pos = {(static_cast<float>(tilePosition.x * tileSize.x)) + spriteCenter.x,
           (static_cast<float>(tilePosition.y * tileSize.y)) +
           spriteCenter.y}; //this updates coordinates in PosEntity


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

