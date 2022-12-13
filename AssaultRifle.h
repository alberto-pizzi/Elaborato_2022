//
// Created by alber on 12/12/2022.
//

#ifndef ELABORATO_ASSAULTRIFLE_H
#define ELABORATO_ASSAULTRIFLE_H

#include "Weapon.h"

class AssaultRifle : public Weapon {
private:
    const sf::Vector2i fileTextureRectAssaultShotSize = {128, 48};
    const sf::Vector2i fileTextureRectAssaultReloadSize = {96, 64};
public:
    AssaultRifle(bool equipped, const sf::Texture &handgunTexture, int totBullets = 150, int damage = 5,
                 float shotDelay = 0.2f, float reloadTime = 5, int magazineCapacity = 30,
                 int remainingBullets = 30);

    void shoot() override;
};


#endif //ELABORATO_ASSAULTRIFLE_H
