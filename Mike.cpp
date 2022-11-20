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
    character.setFillColor(sf::Color::Green); //TODO remove it (for debug)
    character.setPosition(sf::Vector2f(23 * 32, 20 * 32));
    pos = {23 * 32, 20 * 32}; //update coordinates in PosEntity

}

void Mike::drawEntity(sf::RenderWindow &window) {
    window.draw(character); //TODO remove it (for debug)
}
