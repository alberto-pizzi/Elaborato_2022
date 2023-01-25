//
// Created by Alberto Pizzi on 31/12/22.
//

#include "Boss.h"

unsigned int Boss::roundCount = 0;

Boss::Boss(const sf::Texture &bossTexture, const sf::Vector2i &spawnTile, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, sf::Vector2f damageHit, const std::vector<std::vector<Node>> &nodeMap,
           float hitProbability, float hp, sf::Vector2f scaleSize, bool animated, float speed, unsigned int points,
           unsigned int coins, float armor, bool bubble) : Enemy(bossTexture,
                                                                 hp * (static_cast<float>(roundCount) / 2), speed,
                                                                 points,
                                                                 spawnTile,
                                                                 tileSize,
                                                                 rectSkin, BOSS,
                                                                 damageHit, nodeMap, hitProbability, 1,
                                                                 animated,
                                                                 coins, armor) {
    this->sprite.setScale(sf::Vector2f(scaleSize));
    roundCount++;
}
