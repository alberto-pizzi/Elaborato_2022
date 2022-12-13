//
// Created by alber on 10/12/2022.
//

#ifndef ELABORATO_HANDGUN_H
#define ELABORATO_HANDGUN_H

#include "Weapon.h"


class Handgun : public Weapon {
private:
    const sf::Vector2i fileTextureRectHandgunSize = {64, 36};
public:
    Handgun(bool equipped, const sf::Texture &handgunTexture, int totBullets = -999, int damage = 2,
            float shotDelay = 0.4f, float reloadTime = 1, int magazineCapacity = 12,
            int remainingBullets = 12); //handgun has infinite bullets (-999)
    void shoot() override;
};


#endif //ELABORATO_HANDGUN_H
