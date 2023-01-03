//
// Created by alber on 31/12/2022.
//

#ifndef ELABORATO_WARRIOR_H
#define ELABORATO_WARRIOR_H

#include "GameCharacter.h"

class Warrior : public GameCharacter {
private:
    class Shield {
    public:
        float defense;
        sf::Texture shieldTexture;
        sf::Sprite shieldSprite;

        Shield(const sf::Texture &shieldTexture, float defense);

    };

    Shield shield;
public:
    Warrior(const sf::Texture &warriorTexture, const sf::Texture &shieldTexture, const sf::Vector2i &spawnTile,
            const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, float defense, sf::Vector2f damageHit,
            bool animated = true, int hp = 20, float speed = 230.f, unsigned int points = 10, unsigned int coins = 2,
            int armor = 5, bool bubble = false);

    void receiveDamage(float damagePoints) override;

    void drawEntity(sf::RenderWindow &window) override;

};


#endif //ELABORATO_WARRIOR_H
