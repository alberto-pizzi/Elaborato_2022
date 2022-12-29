//
// Created by alber on 29/12/2022.
//

#include "IncreasedWeaponDamage.h"

IncreasedWeaponDamage::IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                             sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, INCREASED_DAMAGE, {32, 32},
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values
    idleBonusBox = {{(1 * animationFrameSize.x) + 22, 2 * animationFrameSize.y + 24, 23, 25}};
    translation = {static_cast<float>(idleBonusBox[0].left % animationFrameSize.x),
                   static_cast<float>(idleBonusBox[0].top % animationFrameSize.y)}; //FIXME

    duration = sf::seconds(20); //FIXME set random seconds
    multiplier = 1.3f; //FIXME set random multiplier
}

void IncreasedWeaponDamage::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setDamage(static_cast<int>(static_cast<float>(character.weapon->getDamage()) * multiplier));
}