//
// Created by alber on 12/12/2022.
//

#ifndef ELABORATO_ASSAULTRIFLE_H
#define ELABORATO_ASSAULTRIFLE_H

#include "Weapon.h"
#include "AssaultRifleBullet.h"

class AssaultRifle : public Weapon {
private:
    const sf::Vector2i fileTextureRectAssaultShotSize = {128, 48};
    const sf::Vector2i fileTextureRectAssaultReloadSize = {96, 64};
    const sf::Vector2f barrelHole = {86, 17}; //FIXME
public:
    AssaultRifle(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &assaultRifleBulletTexture,
                 int totBullets = 150, int damage = 5, float shotDelay = 0.2f, float reloadTime = 1,
                 int magazineCapacity = 30, int remainingBullets = 30);

    void shoot(const sf::Vector2f &normalizedBulletDir) override;
};


#endif //ELABORATO_ASSAULTRIFLE_H
