//
// Created by Alberto Pizzi on 31/12/22.
//

#ifndef ELABORATO_KAMIKAZE_H
#define ELABORATO_KAMIKAZE_H

#include "Enemy.h"

class Kamikaze : public Enemy {
private:
    sf::Clock explosionClock;
    sf::Time explosionTime = sf::seconds(2);
    bool explosionStarted = false;
    sf::CircleShape explosionArea;
    const float explosionRadius = 56;
public:
    Kamikaze(const sf::Texture &kamikazeTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
             const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
             bool animated = true, int hp = 10, float speed = 190.f, unsigned int points = 8, unsigned int coins = 2,
             float armor = 0);

    const sf::Clock &getExplosionClock() const;

    void setExplosionClock(const sf::Clock &explosionClock);

    const sf::Time &getExplosionTime() const;

    void setExplosionTime(const sf::Time &explosionTime);

    bool isExplosionStarted() const;

    void setExplosionStarted(bool explosionStarted);

    void drawEntity(sf::RenderWindow &window) override;

    bool isAbleToHit(const GameCharacter &target, const Dice &hitDice, float hitChance) override;

    void hit(GameCharacter &target, std::vector<std::unique_ptr<Enemy>> &targetEnemies) override;

};


#endif //ELABORATO_KAMIKAZE_H
