//
// Created by Alberto Pizzi on 29/12/22.
//

#ifndef ELABORATO_ZOMBIE_H
#define ELABORATO_ZOMBIE_H

#include "GameCharacter.h"

class Zombie : public GameCharacter {
public:
    //FIXME fix speed because after some time the sprites overlap them
    Zombie(const sf::Texture &zombieTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, bool animated = true, int hp = 15, float speed = 150.f,
           unsigned int points = 5,
           unsigned int coins = 1, int armor = 0, bool bubble = false);

    void move(const sf::Vector2f &offset, float dt) override; //FIXME
};


#endif //ELABORATO_ZOMBIE_H
