//
// Created by alber on 13/01/2023.
//

#ifndef ELABORATO_BOW_H
#define ELABORATO_BOW_H

#include "Weapon.h"

class Bow : public Weapon {
private:
    enum totFramesHandgun {
        IDLE = 1, SHOT = 6, RELOAD = 0,
    };
    const sf::Vector2i fileTextureRectHandgunSize = {32, 32};
    const sf::Vector2f barrelHole = {8, 13};
public:
    Bow(bool equipped, const sf::Texture &bowTexture, const sf::Texture &arrowTexture, float damage = 3,
        int totBullets = -999, sf::Time shotDelay = sf::seconds(3), float reloadTime = 1, int magazineCapacity = 3,
        int remainingBullets = 3); //bow has infinite bullets (-999)
    void shoot(const sf::Vector2f &normalizedBulletDir) override;
};


#endif //ELABORATO_BOW_H
