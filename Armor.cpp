//
// Created by alber on 29/12/2022.
//

#include "Armor.h"

Armor::Armor(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, float quantity, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, ARMOR, {64, 64}, 4,
                false,
                false, true), quantity(quantity) { //those values are the sprite frame size

}

void Armor::doSpecialAction(Mike &character) {
    addPoints(character);
    if (character.getArmor() <= 0)
        character.setArmor(this->quantity);
    else
        character.setArmor(character.getArmor() + this->quantity);
}
