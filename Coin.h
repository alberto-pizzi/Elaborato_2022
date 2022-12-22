//
// Created by alber on 22/12/2022.
//

#ifndef ELABORATO_COIN_H
#define ELABORATO_COIN_H

#include "Bonus.h"

class Coin : public Bonus {
private:
    int value;
    const int nFrames = 8;
    const sf::Vector2i frameSize = {32, 32};
public:
    Coin(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 2,
         sf::Time stayTime = sf::seconds(15));

    void doSpecialAction(GameCharacter &character) override;

    int getValue() const;

    void setValue(int value);

};


#endif //ELABORATO_COIN_H
