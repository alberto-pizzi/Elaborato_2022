//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Boss.h"

Boss::Boss(const sf::Texture &bossTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
           float hitProbability, sf::Vector2f scaleSize, bool animated, float hp, float speed, unsigned int points,
           unsigned int coins, int armor, bool bubble) : Enemy(bossTexture,
                                                               hp, speed,
                                                               points,
                                                               spawnTile,
                                                               tileSize,
                                                               rectSkin, BOSS,
                                                               damageHit, nodeMap, hitProbability, 1,
                                                               animated,
                                                               coins, armor,
                                                               bubble) {
    this->sprite.setScale(sf::Vector2f(scaleSize));
}
