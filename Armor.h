//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_ARMOR_H
#define ELABORATO_ARMOR_H

#include "Bonus.h"

class Armor : public Bonus {
private:
    int quantity;
public:
    Armor(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 6,
          sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_ARMOR_H
