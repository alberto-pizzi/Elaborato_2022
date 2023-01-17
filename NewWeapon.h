//
// Created by alber on 21/12/2022.
//

#ifndef ELABORATO_NEWWEAPON_H
#define ELABORATO_NEWWEAPON_H

#include <memory>
#include <iostream>

#include "GameCharacter.h"
#include "GameException.h"
#include "Weapon.h"
#include "Bonus.h"
#include "Mike.h"




class NewWeapon : public Bonus {
private:
    enum WeaponType {
        HANDGUN = 0, ASSAULT_RIFLE, SHOTGUN,
    };

    TextureManager weaponsTextures;
    std::unique_ptr<Weapon> newWeapon;
    const int totalWeapons = 3;
public:
    NewWeapon(const TextureManager &weaponsTextures, const sf::Texture &bonusTexture, sf::Vector2f spawnCoords,
              int points = 10, sf::Time stayTime = sf::seconds(50));

    //WARNING: call this when you want despawning a new weapon (for startDespawining animation)

    void selectWeaponToSpawn(int selected);

    void doSpecialAction(Mike &character) override;
};


#endif //ELABORATO_NEWWEAPON_H
