//
// Created by alber on 29/12/2022.
//

#include "IncreasedWeaponDamage.h"

IncreasedWeaponDamage::IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                             sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, INCREASED_DAMAGE, sf::Vector2f(),
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    animationFrames.clear();
    for (int i = 0; i < nFrames; i++)
        animationFrames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    currentAnimation.setNotCyclicalAnimation(animationFrames, 1.f);

    duration = sf::seconds(20); //FIXME set random seconds
    multiplier = 1.3f; //FIXME set random multiplier

    stayTimer.restart();
}

void IncreasedWeaponDamage::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setDamage(static_cast<int>(static_cast<float>(character.weapon->getDamage()) * multiplier));
}