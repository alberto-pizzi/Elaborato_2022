//
// Created by alber on 29/12/2022.
//

#include "Ammunition.h"

Ammunition::Ammunition(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int quantity, int points,
                       sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, AMMUNITION, {64, 64}, 2,
                false,
                false,
                true), quantity(
        quantity) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    //FIXME set random quantity
}

void Ammunition::doSpecialAction(Mike &character) {
    addPoints(character);
    if (character.weapon && !character.weapon->isInfiniteBullets())
        character.weapon->setTotalBullets(character.weapon->getTotalBullets() + this->quantity);
}