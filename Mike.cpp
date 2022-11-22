//
// Created by alber on 12/11/2022.
//

#include "Mike.h"

void Mike::move(sf::Vector2f pos) {

}

bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(int hp, int speed, int points, int coins, int armor, bool bubble, int streak) : GameCharacter(hp, speed,
                                                                                                         points, coins,
                                                                                                         armor,
                                                                                                         bubble),
                                                                                           killStreak(streak) {
    //spawning mike
    character.setFillColor(sf::Color::Green); //TODO remove it (for debug)
    character.setPosition(sf::Vector2f(5 * 32, 5 * 32)); //FIXME 23x20
    pos = {(5 * 32) + 16, (5 * 32) + 16}; //this updates coordinates in PosEntity

}

void Mike::drawEntity(sf::RenderWindow &window) {
    window.draw(character); //TODO remove it (for debug)
}

void Mike::moveMike(const sf::Vector2f &offset) {
    character.setPosition(character.getPosition() + offset);
    pos += offset;
}
