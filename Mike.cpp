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
                                                                                                         bubble) {

}
