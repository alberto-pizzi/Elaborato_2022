//
// Created by alber on 29/12/2022.
//

#include "IncreasedWeaponDamage.h"

IncreasedWeaponDamage::IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                             sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, INCREASED_DAMAGE, {64, 64},
                1,
                true,
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values
    duration = sf::seconds(20); //FIXME set random seconds
    multiplier = 1.3f; //FIXME set random multiplier
}

void IncreasedWeaponDamage::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setDamage(static_cast<int>(static_cast<float>(character.weapon->getDamage()) * multiplier));
    character.addToOwnBonuses(INCREASED_DAMAGE, duration);
}