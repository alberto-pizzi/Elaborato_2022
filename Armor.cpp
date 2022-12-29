//
// Created by alber on 29/12/2022.
//

#include "Armor.h"

Armor::Armor(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, ARMOR,
                true,
                false) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    animationFrames.clear();
    for (int i = 0; i < nFrames; i++)
        animationFrames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    currentAnimation.setNotCyclicalAnimation(animationFrames, 1.f);

    quantity = 2; //FIXME set random quantity

    stayTimer.restart();
}

void Armor::doSpecialAction(Mike &character) {
    addPoints(character);
    character.setArmor(character.getArmor() + this->quantity);
}
