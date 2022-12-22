//
// Created by alber on 22/12/2022.
//

#include "Coin.h"

int Coin::getValue() const {
    return value;
}

void Coin::setValue(int value) {
    Coin::value = value;
}

void Coin::doSpecialAction(GameCharacter &character) {
    character.setCoins(character.getCoins() + this->value);
}

Coin::Coin(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 32, 32, 32}}, COINS, true) {


    animationFrames.clear();
    for (int i = 0; i < nFrames; i++) //1 because the first vector element already exist
        animationFrames.emplace_back(i * frameSize.x, 0, frameSize.x, frameSize.y);
    currentAnimation.setNotCyclicalAnimation(animationFrames, 1.f);

    this->stayTimer.restart();
}

