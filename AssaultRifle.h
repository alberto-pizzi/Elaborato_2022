//
// Created by alber on 12/12/2022.
//

#ifndef ELABORATO_ASSAULTRIFLE_H
#define ELABORATO_ASSAULTRIFLE_H

#include "Weapon.h"

class AssaultRifle : public Weapon {
private:
    enum totFramesAssaultRifle {
        IDLE = 1, SHOT = 16, RELOAD = 17,
    };
    const sf::Vector2i fileTextureRectAssaultShotSize = {128, 48};
    const sf::Vector2i fileTextureRectAssaultReloadSize = {96, 64};
    const sf::Vector2f barrelHole = {86, 17};
public:
    AssaultRifle(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &assaultRifleBulletTexture,
                 int totBullets = 150, int damage = 7, sf::Time shotDelay = sf::seconds(0.2f), float reloadTime = 1,
                 int magazineCapacity = 30, int remainingBullets = 30);

    void shoot(const sf::Vector2f &normalizedBulletDir) override;
};


#endif //ELABORATO_ASSAULTRIFLE_H
