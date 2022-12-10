//
// Created by alber on 10/12/2022.
//

#ifndef ELABORATO_HANDGUN_H
#define ELABORATO_HANDGUN_H

#include "Weapon.h"


class Handgun : public Weapon {
private:
    const sf::Vector2i fileTextureRectHandgunSize = {64, 32};
public:
    Handgun(bool equipped, int totBullets = -999, int damage = 2, float shotDelay = 1, float reloadTime = 5,
            int magazineCapacity = 12, int remainingBullets = 12); //handgun has infinite bullets (-999)
    void shoot() override;
};


#endif //ELABORATO_HANDGUN_H
