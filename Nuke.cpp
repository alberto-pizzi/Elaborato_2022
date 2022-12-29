//
// Created by Alberto Pizzi on 29/12/22.
//

#include "Nuke.h"
#include "Mike.h"

Nuke::Nuke(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, NUKE, {32, 32},
                true,
                false) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    animationFrames.clear();
    for (int i = 0; i < nFrames; i++)
        animationFrames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    currentAnimation.setNotCyclicalAnimation(animationFrames, 1.f);

    stayTimer.restart();
}

void Nuke::doSpecialAction(Mike &character) {
    addPoints(character);
    //kill all action is made by Spawner class
}

