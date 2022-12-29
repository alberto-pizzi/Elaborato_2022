//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_LIFEPOINTS_H
#define ELABORATO_LIFEPOINTS_H

#include "Bonus.h"

class LifePoints : public Bonus {
private:
    int quantity;
    const int nFrames = 8;
public:
    LifePoints(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 8,
               sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_LIFEPOINTS_H
