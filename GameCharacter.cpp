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

GameCharacter::GameCharacter(const sf::Texture &tex, int hp, float speed, int points, int coins, int armor, bool bubble)
        : HP(hp), speed(speed),
          points(points),
          coins(coins),
          armor(armor),
          bubble(bubble), texture(tex) {
    //sprite.setPosition(sf::Vector2f(5 * 32, 5 * 32));
    //pos = {(5 * 32) + 16, (5 * 32) + 16};
    sprite.setTexture(texture);


}


const sf::Sprite &GameCharacter::getSprite() const {
    return sprite;
}

GameCharacter::~GameCharacter() = default;

