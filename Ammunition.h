//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_AMMUNITION_H
#define ELABORATO_AMMUNITION_H

#include "Bonus.h"
#include "Mike.h"

class Ammunition : public Bonus {
private:
    int quantity;
public:
    Ammunition(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 5,
               sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_AMMUNITION_H
