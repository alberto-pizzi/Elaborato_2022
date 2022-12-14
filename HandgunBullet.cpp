//
// Created by alber on 18/12/2022.
//

#include "HandgunBullet.h"

HandgunBullet::HandgunBullet(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
                             const sf::Vector2f &weaponPos, float degrees, const sf::Vector2f &rotationOrigin,
                             const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir) : Bullet(tex, speed,
                                                                                                      rotationOrigin,
                                                                                                      degrees,
                                                                                                      weaponScale,
                                                                                                      bulletDir) {
    sf::Vector2f bulletOrigin;

    if (weaponScale.x > 0)
        bulletOrigin = {static_cast<float>(weaponPos.x +
                                           (barrelHole.x - rotationOrigin.x) * std::cos((M_PI * (-degrees)) / 180) +
                                           (tex.getSize().y - -rotationOrigin.y) * std::sin((M_PI * (-degrees)) / 180)),
                        static_cast<float>(weaponPos.y +
                                           (barrelHole.x - rotationOrigin.x) * std::sin((M_PI * (degrees)) / 180) +
                                           (tex.getSize().y - rotationOrigin.y) * std::cos((M_PI * (-degrees)) / 180))};
    else
        bulletOrigin = {static_cast<float>(weaponPos.x -
                                           (barrelHole.x - rotationOrigin.x) * std::cos((M_PI * (degrees)) / 180) -
                                           (tex.getSize().y - rotationOrigin.y) * std::sin((M_PI * (degrees)) / 180)),
                        static_cast<float>(weaponPos.y +
                                           (barrelHole.x - rotationOrigin.x) * std::sin((M_PI * (-degrees)) / 180) +
                                           (tex.getSize().y - rotationOrigin.y) * std::cos((M_PI * (degrees)) / 180))};

    this->bulletSprite.setPosition(bulletOrigin);
}
