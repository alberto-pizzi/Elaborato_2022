//
// Created by alber on 29/12/2022.
//

#include "ProtectionBubble.h"

ProtectionBubble::ProtectionBubble(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points,
                                   sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, PROTECTION_BUBBLE, {32, 32},
                true,
                true) { //those values are the sprite frame size //FIXME correct with the correct texture frame values

    this->sprite.setScale(sf::Vector2f(1.5, 1.5)); //TODO insert it into parent class
    idleBonusBox = {{(0 * animationFrameSize.x) + 22, 2 * animationFrameSize.y + 24, 23, 25}};
    translation = {static_cast<float>(idleBonusBox[0].left % animationFrameSize.x),
                   static_cast<float>(idleBonusBox[0].top % animationFrameSize.y)}; //FIXME

    //TODO insert these lines into bonus son classes
    this->animationFrames = idleBonusBox;
    currentAnimation.idleFrames = idleBonusBox;

    duration = sf::seconds(15); //FIXME set random seconds

}

void ProtectionBubble::doSpecialAction(Mike &character) {
    addPoints(character);
    character.setBubble(true);
}