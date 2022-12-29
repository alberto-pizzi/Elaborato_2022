//
// Created by alber on 29/12/2022.
//

#include "ProtectionBubble.h"

ProtectionBubble::ProtectionBubble(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                   sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, PROTECTION_BUBBLE,
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    animationFrames.clear();
    for (int i = 0; i < nFrames; i++)
        animationFrames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    currentAnimation.setNotCyclicalAnimation(animationFrames, 1.f);

    duration = sf::seconds(15); //FIXME set random seconds

    stayTimer.restart();
}

void ProtectionBubble::doSpecialAction(Mike &character) {
    addPoints(character);
    character.setBubble(true);
}