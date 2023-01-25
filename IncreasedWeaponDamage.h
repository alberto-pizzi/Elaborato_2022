//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_INCREASEDWEAPONDAMAGE_H
#define ELABORATO_INCREASEDWEAPONDAMAGE_H

#include "Bonus.h"

class IncreasedWeaponDamage : public Bonus {
private:
    float multiplier;
public:
    IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, float multiplier, int points = 10,
                          sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_INCREASEDWEAPONDAMAGE_H
