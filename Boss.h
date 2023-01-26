//
// Created by Alberto Pizzi on 31/12/22.
//

#ifndef ELABORATO_BOSS_H
#define ELABORATO_BOSS_H

#include "GameCharacter.h"
#include "Scepter.h"

class Boss : public GameCharacter {
private:
    const sf::Vector2f scaleSize = {4, 4};
    static unsigned int roundCount; //this attribute is increased each boss round
    bool bubble = false;
    float maxMovingRange = 5 * 32;
    sf::Vector2f spawnOrigin;
public:
    Boss(const sf::Texture &bossTexture, const sf::Texture &scepterTex, const sf::Texture &energyTex,
         const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin,
         sf::Vector2f damageHit, float hp = 80, bool animated = true, float speed = 200.f, unsigned int points = 100,
         unsigned int coins = 12, float armor = 10);

    void updateCharacterColor() override;

    void receiveDamage(float damagePoints) override;

    float getMaxMovingRange() const;

    const sf::Vector2f &getSpawnOrigin() const;
};


#endif //ELABORATO_BOSS_H
