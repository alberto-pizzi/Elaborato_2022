//
// Created by alber on 29/12/2022.
//

#include "Armor.h"

Armor::Armor(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, ARMOR, {64, 64}, 4,
                false,
                false, true) { //those values are the sprite frame size
    quantity = 2; //FIXME set random quantity

}

void Armor::doSpecialAction(Mike &character) {
    addPoints(character);
    if (character.getArmor() <= 0)
        character.setArmor(this->quantity);
    else
        character.setArmor(character.getArmor() + this->quantity);
}
