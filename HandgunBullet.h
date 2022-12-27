//
// Created by alber on 18/12/2022.
//

#ifndef ELABORATO_HANDGUNBULLET_H
#define ELABORATO_HANDGUNBULLET_H

#include "Bullet.h"

class HandgunBullet : public Bullet {
public:
    HandgunBullet(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
                  const sf::Vector2f &weaponPos, float degrees, const sf::Vector2f &rotationOrigin,
                  const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir);
};


#endif //ELABORATO_HANDGUNBULLET_H
