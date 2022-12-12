//
// Created by alber on 10/12/2022.
//

#ifndef ELABORATO_WEAPON_H
#define ELABORATO_WEAPON_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <string>

#include "Animation.h"
#include "TextureManager.h"

class Weapon {
private:

    class Magazine {
    public:
        int totalCapacity;
        int remainingBullets;

        Magazine(int magazineCapacity, int remainingBullets);
    };
    sf::Vector2i fileTextureRectWeaponSize;
protected:
    int totalBullets;
    bool infiniteBullets = false;
    int damage;
    float reloadTime;
    bool equipped;
    float nextShotDelay; //in seconds
    std::string weaponName;
    sf::Texture weaponTexture;
    Magazine magazine;
    std::vector<sf::IntRect> idleWeapon;
    std::vector<sf::IntRect> shot;
    std::vector<sf::IntRect> reload;
public:
    sf::Sprite weaponSprite;
    Animation currentAnimation{idleWeapon, 10.0f};

    Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, float shotDelay,
           float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
           std::string weaponName, bool infiniteBullets = false);

    virtual ~Weapon();

    virtual void shoot() = 0;

    bool reloadWeapon();

    bool thereAreRemainingBullets() const;

    void drawWeapon(sf::RenderWindow &window);

    float getNextShotDelay() const;

    int getTotalBullets() const;

    bool isInfiniteBullets() const;

    const Magazine &getMagazine() const;

};


#endif //ELABORATO_WEAPON_H
