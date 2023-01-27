//
// Created by alber on 25/01/2023.
//

#ifndef ELABORATO_SCEPTER_H
#define ELABORATO_SCEPTER_H

#include "Weapon.h"

class Scepter : public Weapon {
private:
    enum totFramesHandgun {
        IDLE = 1, SHOT = 4, RELOAD = 0,
    };
    const sf::Vector2i fileTextureRectScepterSize = {32, 32};
    const sf::Vector2f barrelHole = {23, 15};
public:
    Scepter(bool equipped, const sf::Texture &scepterTex, const sf::Texture &energyBulletTex, sf::Vector2f bossScale,
            float damage = 5, int totBullets = -999, sf::Time shotDelay = sf::seconds(3), float reloadTime = 1,
            int magazineCapacity = 3, int remainingBullets = 3); //scepter has infinite bullets (-999)
    void shoot(const sf::Vector2f &normalizedBulletDir) override;
};


#endif //ELABORATO_SCEPTER_H
