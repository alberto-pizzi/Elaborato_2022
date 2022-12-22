//
// Created by alber on 21/12/2022.
//

#include "NewWeapon.h"

void NewWeapon::doSpecialAction(GameCharacter &character) {
    //replace current weapon with a new weapon
    character.weapon = std::move(this->newWeapon);
    character.weapon->setEquipped(true);
}

void NewWeapon::selectWeaponToSpawn(int selected) {
    int totBullets;

    switch (selected) {
        case HANDGUN:
            this->idleWeaponBox = {{16, 152, 21, 25}};
            newWeapon = std::unique_ptr<Weapon>(new Handgun(false, weaponsTextures.getTextureRef("handgun"),
                                                            weaponsTextures.getTextureRef("bullet")));
            break;
        case ASSAULT_RIFLE:
            this->idleWeaponBox = {{76, 152, 30, 25}};
            newWeapon = std::unique_ptr<Weapon>(new AssaultRifle(false, weaponsTextures.getTextureRef("assaultRifle"),
                                                                 weaponsTextures.getTextureRef("bullet")));
            break;
        case SHOTGUN:
            this->idleWeaponBox = {{142, 152, 25, 25}};
            newWeapon = std::unique_ptr<Weapon>(new Shotgun(false, weaponsTextures.getTextureRef("shotgun"),
                                                            weaponsTextures.getTextureRef("bullet")));
            break;
    }
    this->translation = {static_cast<float>(idleWeaponBox[0].left % frameSize.x),
                         static_cast<float>(idleWeaponBox[0].top % frameSize.y)};

}

NewWeapon::NewWeapon(const TextureManager &weaponsTextures, const sf::Texture &bonusTexture, sf::Vector2f spawnCoords,
                     int points, sf::Time stayTime)
        : Bonus(bonusTexture, points, stayTime, spawnCoords, {{0, 64, 64, 64}}, NEW_WEAPON, false) {


    Dice dice(totalWeapons);

    this->sprite.setScale(sf::Vector2f(2, 2));
    this->weaponsTextures = weaponsTextures;

    this->selectWeaponToSpawn(dice.roll(1));
    this->animationFrames = this->idleWeaponBox;
    this->currentAnimation.idleFrames = this->idleWeaponBox;


    despawnFrames.reserve(DESPAWN);
    for (int i = 0; i < DESPAWN; i++)
        despawnFrames.emplace_back(i * frameSize.x, 1 * frameSize.y, frameSize.x, frameSize.y);


    //currentAnimation.setNotCyclicalAnimation(animationFrames,10.0f);


    this->stayTimer.restart();
}

void NewWeapon::startDespawining() {
    if (!despawnStarted) {
        currentAnimation.setNotCyclicalAnimation(despawnFrames, 1.0f);
        this->sprite.setPosition(this->sprite.getPosition() - this->translation);
        despawnStarted = true;
    }
}
