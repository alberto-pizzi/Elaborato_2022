//
// Created by Alberto Pizzi on 29/12/22.
//

#include "Nuke.h"
#include "Mike.h"

Nuke::Nuke(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, NUKE, {32, 32},
                true,
                false) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    idleBonusBox = {{(5 * animationFrameSize.x) + 22, 2 * animationFrameSize.y + 24, 23, 25}};
    translation = {static_cast<float>(idleBonusBox[0].left % animationFrameSize.x),
                   static_cast<float>(idleBonusBox[0].top % animationFrameSize.y)}; //FIXME
}

void Nuke::doSpecialAction(Mike &character) {
    addPoints(character);
    //kill all action is made by Spawner class
}

