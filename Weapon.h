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
#include <memory>
#include <vector>

#include "Animation.h"
#include "TextureManager.h"
#include "Bullet.h"

class ArenaMap;

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
    enum Directions {
        LEFT = 0, RIGHT, UP, DOWN,
    };
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
    float degrees;

    //bullet
    std::vector<std::unique_ptr<Bullet>> bullets;
    sf::Texture bulletTexture;
public:
    bool isCut = false;
    int cutValueX = 0;
    sf::Sprite weaponSprite;
    sf::RectangleShape hitBox;
    sf::Vector2f startCenterForTranslation[4]; //4 directions
    Animation currentAnimation{idleWeapon, 10.0f};

    Weapon(bool equipped, const sf::Texture &weaponTexture, int totBullets, int damage, float shotDelay,
           float reloadTime, int magazineCapacity, int remainingBullets, const sf::Vector2i &texRectWeapon,
           std::string weaponName, bool infiniteBullets = false);

    virtual ~Weapon();

    virtual void shoot(const sf::Vector2f &normalizedBulletDir) = 0;

    virtual bool reloadWeapon();

    bool thereAreRemainingBullets() const;

    void drawWeapon(sf::RenderWindow &window);

    float getNextShotDelay() const;

    int getTotalBullets() const;

    bool isInfiniteBullets() const;

    const Magazine &getMagazine() const;

    const std::string &getWeaponName() const;

    float getDegrees() const;

    void setDegrees(float degrees);

    const std::vector<std::unique_ptr<Bullet>> &getBullets() const;

    void drawBullets(sf::RenderWindow &window, float dt) const;

    void updateBullets(ArenaMap *map);

    const sf::Vector2i &getFileTextureRectWeaponSize() const;

};


#endif //ELABORATO_WEAPON_H
