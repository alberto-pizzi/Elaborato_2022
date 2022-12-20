//
// Created by alber on 20/12/2022.
//

#ifndef ELABORATO_SHOTGUNBULLET_H
#define ELABORATO_SHOTGUNBULLET_H

#include "Bullet.h"

class ShotgunBullet : public Bullet {
public:
    ShotgunBullet(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
                  const sf::Vector2f &weaponPos, float degrees, const sf::Vector2f &rotationOrigin,
                  const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir);
};


#endif //ELABORATO_SHOTGUNBULLET_H
