//
// Created by alber on 29/12/2022.
//

#include "Ammunition.h"

Ammunition::Ammunition(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, AMMUNITION, {64, 64}, 2,
                false,
                false,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    quantity = 30; //FIXME set random quantity
}

void Ammunition::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setTotalBullets(character.weapon->getTotalBullets() + this->quantity);
}