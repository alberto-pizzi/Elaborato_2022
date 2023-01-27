//
// Created by alber on 20/12/2022.
//

#include "ShotgunBullet.h"

ShotgunBullet::ShotgunBullet(const sf::Texture &tex, float speed, const sf::Vector2f &barrelHole,
                             const sf::Vector2f &weaponPos, float degrees, const sf::Vector2f &rotationOrigin,
                             const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir,
                             sf::Vector2f bulletScale, int whichBullet) : Bullet(tex, speed,
                                                                                 rotationOrigin,
                                                                                 degrees,
                                                                                 weaponScale,
                                                                                 bulletDir, weaponPos, barrelHole,
                                                                                 bulletScale) {

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
}

