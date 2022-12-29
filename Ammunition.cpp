//
// Created by alber on 29/12/2022.
//

#include "Ammunition.h"

Ammunition::Ammunition(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, AMMUNITION, {32, 32},
                true,
                false) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    idleBonusBox = {{(2 * animationFrameSize.x) + 22, 2 * animationFrameSize.y + 24, 23, 25}};
    translation = {static_cast<float>(idleBonusBox[0].left % animationFrameSize.x),
                   static_cast<float>(idleBonusBox[0].top % animationFrameSize.y)}; //FIXME
    quantity = 30; //FIXME set random quantity
}

void Ammunition::doSpecialAction(Mike &character) {
    addPoints(character);
    character.weapon->setTotalBullets(character.weapon->getTotalBullets() + this->quantity);
}