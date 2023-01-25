//
// Created by alber on 13/01/2023.
//

#include "Archer.h"

Archer::Archer(const sf::Texture &archerTexture, const sf::Texture &bowTexture, const sf::Texture &arrowTexture,
               const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin,
               sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap, bool animated, float hp,
               float speed,
               unsigned int points, unsigned int coins, float armor, bool bubble)
        : Enemy(archerTexture, hp, speed, points, spawnTile,
                tileSize, rectSkin, ARCHER, damageHit, nodeMap, 100, 200,
                animated,
                coins, armor, bubble) {

    weapon = std::unique_ptr<Weapon>(new Bow(true, bowTexture, arrowTexture, damageHit.y)); //max value of damage hit
}

void Archer::hit(GameCharacter &target, std::vector<std::unique_ptr<Enemy>> &targetEnemies) {
    if (weapon->shotClock.getElapsedTime() >= weapon->getNextShotDelay()) {
        sf::Vector2f origin = spriteCenter;
        sf::Vector2f translation = target.getSpriteCenter() - spriteCenter;
        weapon->shoot(normalize(translation));
    }
}
