//
// Created by alber on 29/12/2022.
//

#include "ProtectionBubble.h"

ProtectionBubble::ProtectionBubble(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                   sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, PROTECTION_BUBBLE, {32, 32},
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    animationFrames = idleWeaponBox;
    currentAnimation.idleFrames = idleWeaponBox;


    //currentAnimation.setNotCyclicalAnimation(animationFrames,10.0f);

    stayTimer.restart();

    duration = sf::seconds(15); //FIXME set random seconds

    stayTimer.restart();
}

void ProtectionBubble::doSpecialAction(Mike &character) {
    addPoints(character);
    character.setBubble(true);
}