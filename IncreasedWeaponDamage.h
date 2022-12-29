//
// Created by alber on 29/12/2022.
//

#ifndef ELABORATO_INCREASEDWEAPONDAMAGE_H
#define ELABORATO_INCREASEDWEAPONDAMAGE_H

#include "Bonus.h"

class IncreasedWeaponDamage : public Bonus {
private:
    float multiplier;
    const int nFrames = 8;
    const sf::Vector2i frameSize = {32, 32};
public:
    IncreasedWeaponDamage(const sf::Texture &bonusTexture, sf::Vector2f spawnCoords, int points = 10,
                          sf::Time stayTime = sf::seconds(25));

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_INCREASEDWEAPONDAMAGE_H
