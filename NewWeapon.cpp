//
// Created by alber on 21/12/2022.
//

#include "NewWeapon.h"

void NewWeapon::doSpecialAction(Mike &character) {
    addPoints(character);
    //replace current weapon with a new weapon
    character.weapon = std::move(newWeapon);
    character.weapon->setEquipped(true);

    //play the weapon picked up sound
    character.weapon->playWeaponPickedUpSound();
}

void NewWeapon::selectWeaponToSpawn(int selected) {
    int totBullets;

    switch (selected) {
        case HANDGUN:
            idleBonusBox = {{16, 152, 21, 25}};
            newWeapon = std::unique_ptr<Weapon>(new Handgun(false, weaponsTextures.getTextureRef("handgun"),
                                                            weaponsTextures.getTextureRef("bullet")));
            break;
        case ASSAULT_RIFLE:
            idleBonusBox = {{142, 152, 25, 25}};

            newWeapon = std::unique_ptr<Weapon>(new AssaultRifle(false, weaponsTextures.getTextureRef("assaultRifle"),
                                                                 weaponsTextures.getTextureRef("bullet")));
            break;
        case SHOTGUN:
            idleBonusBox = {{76, 152, 30, 25}};
            newWeapon = std::unique_ptr<Weapon>(new Shotgun(false, weaponsTextures.getTextureRef("shotgun"),
                                                            weaponsTextures.getTextureRef("bullet")));
            break;
        default:
            std::cerr << "ERROR: SELECTED WEAPON NOT EXIST" << std::endl;
            break;
    }
    translation = {static_cast<float>(idleBonusBox[0].left % bonusFrameSize.x),
                   static_cast<float>(idleBonusBox[0].top % bonusFrameSize.y)};

}

NewWeapon::NewWeapon(const TextureManager &weaponsTextures, const sf::Texture &bonusTexture, sf::Vector2f spawnCoords,
                     int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, NEW_WEAPON, {64, 64}, 0,
                false,
                false, true) {

    Dice dice(totalWeapons - 1); //TODO optimize it when will be implemented random spawning algorithm

    sprite.setScale(sf::Vector2f(2, 2));
    this->weaponsTextures = weaponsTextures;

    selectWeaponToSpawn(dice.roll(1));

}
