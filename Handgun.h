//
// Created by alber on 10/12/2022.
//

#ifndef ELABORATO_HANDGUN_H
#define ELABORATO_HANDGUN_H

#include "Weapon.h"
#include "HandgunBullet.h"


class Handgun : public Weapon {
private:
    enum totFramesHandgun {
        IDLE = 1, SHOT = 12, RELOAD = 17,
    };
    const sf::Vector2i fileTextureRectHandgunSize = {64, 36};
    const sf::Vector2f barrelHole = {31, 13};
public:
    Handgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
            int totBullets = -999, int damage = 4, sf::Time shotDelay = sf::seconds(0.4f), float reloadTime = 1,
            int magazineCapacity = 12, int remainingBullets = 12); //handgun has infinite bullets (-999)
    void shoot(const sf::Vector2f &normalizedBulletDir) override;
};


#endif //ELABORATO_HANDGUN_H
