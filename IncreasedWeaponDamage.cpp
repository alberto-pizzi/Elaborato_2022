//
// Created by alber on 29/12/2022.
//

#include "IncreasedWeaponDamage.h"

IncreasedWeaponDamage::IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords,
                                             float multiplier, int points,
                                             sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, INCREASED_DAMAGE, {64, 64},
                1,
                false,
                true,
                true), multiplier(
        multiplier) { //those values are the sprite frame size //FIXME correct with the correct texture frame values
    duration = sf::seconds(20);
}

void IncreasedWeaponDamage::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setDamage(character.weapon->getDamage() * multiplier);
    character.addToOwnBonuses(INCREASED_DAMAGE, duration);
}