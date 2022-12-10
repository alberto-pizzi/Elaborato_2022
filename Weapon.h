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

    Magazine magazine;
    sf::Vector2i fileTextureRectWeaponSize;
protected:
    int totalBullets;
    int damage;
    float reloadTime;
    bool equipped;
    float nextShotDelay; //in seconds
    std::string weaponName;
    sf::Texture weaponTexture;
    std::vector<sf::IntRect> idleWeapon;
public:
    sf::Sprite weaponSprite;

    Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, float shotDelay,
           float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
           std::string weaponName);

    virtual ~Weapon();

    virtual void shoot() = 0;

    bool reloadWeapon();

    void drawWeapon(sf::RenderWindow &window);

};


#endif //ELABORATO_WEAPON_H
