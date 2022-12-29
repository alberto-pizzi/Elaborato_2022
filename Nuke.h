//
// Created by Alberto Pizzi on 29/12/22.
//

#ifndef ELABORATO_NUKE_H
#define ELABORATO_NUKE_H

#include "Bonus.h"
#include "Mike.h"

class Nuke : public Bonus {
private:
    const int nFrames = 8;
public:
    Nuke(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 35,
         sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_NUKE_H
