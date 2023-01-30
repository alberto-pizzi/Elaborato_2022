//
// Created by alber on 13/12/2022.
//

#ifndef ELABORATO_SHOTGUN_H
#define ELABORATO_SHOTGUN_H

#include "Weapon.h"
#include "ShotgunBullet.h"

class ArenaMap;

class Shotgun : public Weapon {
private:
    enum totFramesShotgun {
        IDLE = 1, SHOT = 14, RELOAD = 14,
    };
    const sf::Vector2i fileTextureRectShotgunShotSize = {160, 32};
    const sf::Vector2i fileTextureRectShotgunReloadSize = {128, 32};
    const sf::Vector2f barrelHole = {98, 15};
    float bulletRange = 5 * 32;
public:
    Shotgun(bool equipped, const sf::Texture &handgunTexture, const sf::Texture &shotgunBulletTexture,
            int totBullets = 32, int damage = 15, sf::Time shotDelay = sf::seconds(0.7), float reloadTime = 1,
            int magazineCapacity = 8, int remainingBullets = 8);

    void shoot(const sf::Vector2f &normalizedBulletDir) override;

    void updateBullets(std::shared_ptr<ArenaMap> &map, GameCharacter &enemy) override;

    bool reloadWeapon() override;
};


#endif //ELABORATO_SHOTGUN_H
