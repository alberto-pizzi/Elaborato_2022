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

GameCharacter::GameCharacter(int hp, int speed, int points, int coins, int armor, bool bubble) : HP(hp), speed(speed),
                                                                                                 points(points),
                                                                                                 coins(coins),
                                                                                                 armor(armor),
                                                                                                 bubble(bubble) {
    //TODO remove it (for debug)
    character.setSize(sf::Vector2f(32, 32));
    character.setFillColor(sf::Color::Blue);
}

const sf::RectangleShape &GameCharacter::getCharacter() const {
    return character;
}

