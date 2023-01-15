//
// Created by alber on 20/12/2022.
//

#include "ShotgunBullet.h"

ShotgunBullet::ShotgunBullet(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
                             const sf::Vector2f &weaponPos,
                             float degrees, const sf::Vector2f &rotationOrigin, const sf::Vector2f &weaponScale,
                             const sf::Vector2f &bulletDir, int whichBullet) : Bullet(tex, speed,
                                                                                      rotationOrigin,
                                                                                      degrees,
                                                                                      weaponScale,
                                                                                      bulletDir) {

    sf::Vector2f bulletOrigin;

    if (weaponScale.x > 0)
        bulletOrigin = {static_cast<float>(weaponPos.x +
                                           (barrelHole.x - rotationOrigin.x) * std::cos((M_PI * (-degrees)) / 180) +
                                           (tex.getSize().y - rotationOrigin.y) *
                                           std::sin((M_PI * (-degrees)) / 180)),
                        static_cast<float>(weaponPos.y +
                                           (barrelHole.x - rotationOrigin.x) * std::sin((M_PI * (degrees)) / 180) +
                                           (tex.getSize().y + tex.getSize().y / 2 - rotationOrigin.y) *
                                           std::cos((M_PI * (-degrees)) / 180))};
    else
        bulletOrigin = {static_cast<float>(weaponPos.x -
                                           (barrelHole.x - rotationOrigin.x) * std::cos((M_PI * (degrees)) / 180) -
                                           (tex.getSize().y - rotationOrigin.y) *
                                           std::sin((M_PI * (degrees)) / 180)),
                        static_cast<float>(weaponPos.y +
                                           (barrelHole.x - rotationOrigin.x) * std::sin((M_PI * (-degrees)) / 180) +
                                           (tex.getSize().y + tex.getSize().y / 2 - rotationOrigin.y) *
                                           std::cos((M_PI * (degrees)) / 180))};

    switch (whichBullet) {
        case 1:
            if (weaponScale.x > 0)
                bulletSprite.setRotation(bulletSprite.getRotation() - deltaDegrees);
            else
                bulletSprite.setRotation(bulletSprite.getRotation() + deltaDegrees);
            break;
        case 2:
            //standard trajectory (so rotation)
            break;
        case 3:
            if (weaponScale.x > 0)
                bulletSprite.setRotation(bulletSprite.getRotation() + deltaDegrees);
            else
                bulletSprite.setRotation(bulletSprite.getRotation() - deltaDegrees);
            break;
        default:
            std::cerr << "INVALID SELECTED BULLET" << std::endl;
            break;
    }

    bulletSprite.setPosition(bulletOrigin);
}

