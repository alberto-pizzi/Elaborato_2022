//
// Created by alber on 29/12/2022.
//

#include "LifePoints.h"

LifePoints::LifePoints(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, float quantity, int points,
                       sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, LIFE_POINTS, {64, 64}, 3,
                false,
                false,
                true), quantity(
        quantity) { //those values are the sprite frame size

}

void LifePoints::doSpecialAction(Mike &character) {
    addPoints(character);
    if (character.getHp() + this->quantity <= character.getDefaultHp())
        character.setHp(character.getHp() + this->quantity);
    else
        character.setHp(character.getDefaultHp());
}