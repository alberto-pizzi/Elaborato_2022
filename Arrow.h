//
// Created by alber on 13/01/2023.
//

#ifndef ELABORATO_ARROW_H
#define ELABORATO_ARROW_H

#include "Bullet.h"

class Arrow : public Bullet {
public:
    Arrow(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
          const sf::Vector2f &weaponPos, float degrees, const sf::Vector2f &rotationOrigin,
          const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir);
};


#endif //ELABORATO_ARROW_H
