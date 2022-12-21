//
// Created by alber on 18/12/2022.
//

#ifndef ELABORATO_BULLET_H
#define ELABORATO_BULLET_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include "PosEntity.h"

class GameCharacter; //FIXME forward declaration

class Bullet : public PosEntity {
protected:
    float bulletSpeed;
    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;
    sf::Vector2f bulletDir;
public:
    Bullet(const sf::Texture &tex, float speed, const sf::Vector2f &rotationOrigin, float degrees,
           const sf::Vector2f &weaponScale, const sf::Vector2f &bulletDir);

    bool checkEnemyCollision(const GameCharacter &target);


    virtual void move(const sf::Vector2f &offset, float dt); // NOLINT(modernize-use-override)

    const sf::Sprite &getBulletSprite() const;

    const sf::Texture &getBulletTexture() const;

    void setBulletTexture(const sf::Texture &bulletTexture);

    const sf::Vector2f &getBulletDir() const;

    float getBulletSpeed() const;

};


#endif //ELABORATO_BULLET_H
