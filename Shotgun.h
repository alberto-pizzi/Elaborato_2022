//
// Created by alber on 13/12/2022.
//

#ifndef ELABORATO_SHOTGUN_H
#define ELABORATO_SHOTGUN_H

#include "Weapon.h"

class Shotgun : public Weapon {
private:
    const sf::Vector2i fileTextureRectShotgunShotSize = {160, 32};
    const sf::Vector2i fileTextureRectShotgunReloadSize = {128, 32};
public:
    Shotgun(bool equipped, const sf::Texture &handgunTexture, int totBullets = 32, int damage = 15,
            float shotDelay = 0.7f, float reloadTime = 1, int magazineCapacity = 8,
            int remainingBullets = 8);

    void shoot() override;
};


#endif //ELABORATO_SHOTGUN_H
