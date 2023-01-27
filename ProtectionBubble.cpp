//
// Created by alber on 29/12/2022.
//

#include "ProtectionBubble.h"

ProtectionBubble::ProtectionBubble(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                   sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, PROTECTION_BUBBLE, {64, 64},
                0,
                false,
                true,
                true) { //those values are the sprite frame size


    duration = sf::seconds(15);

}

void ProtectionBubble::doSpecialAction(Mike &character) {
    addPoints(character);
    character.setBubble(true);
    character.addToOwnBonuses(PROTECTION_BUBBLE, duration);
}