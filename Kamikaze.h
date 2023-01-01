//
// Created by Alberto Pizzi on 31/12/22.
//

#ifndef ELABORATO_KAMIKAZE_H
#define ELABORATO_KAMIKAZE_H

#include "GameCharacter.h"

class Kamikaze : public GameCharacter {
private:
    sf::Clock explosionClock;
    sf::Time explosionTime = sf::seconds(2);
    bool explosionStarted = false;
public:
    //FIXME fix speed because after some time the sprites overlap them
    Kamikaze(const sf::Texture &kamikazeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
             const sf::Vector2i &rectSkin, bool animated = true, int hp = 10, float speed = 200.f,
             unsigned int points = 8,
             unsigned int coins = 2, int armor = 0, bool bubble = false);

    const sf::Clock &getExplosionClock() const;

    void setExplosionClock(const sf::Clock &explosionClock);

    const sf::Time &getExplosionTime() const;

    void setExplosionTime(const sf::Time &explosionTime);

    bool isExplosionStarted() const;

    void setExplosionStarted(bool explosionStarted);
};


#endif //ELABORATO_KAMIKAZE_H
