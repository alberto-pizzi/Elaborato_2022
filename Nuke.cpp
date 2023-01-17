//
// Created by Alberto Pizzi on 29/12/22.
//

#include "Nuke.h"
#include "Mike.h"

Nuke::Nuke(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, NUKE, {64, 64}, 5,
                false,
                false, true) { //those values are the sprite frame size

}

void Nuke::doSpecialAction(Mike &character) {
    addPoints(character);
    //kill all action is made by Spawner class
}

