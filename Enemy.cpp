//
// Created by alber on 10/01/2023.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Texture &tex, int hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
             const std::vector<std::vector<Node>> &nodeMap, float hitRange, bool animated, unsigned int coins,
             int armor,
             bool bubble) : GameCharacter(tex, hp, speed,
                                          points,
                                          tilePosition,
                                          tileSize,
                                          rectSkin,
                                          characterType,
                                          damageHit,
                                          hitRange,
                                          animated, coins,
                                          armor, bubble),
                            ai(nodeMap) {

}

void Enemy::followPath(const std::vector<Node> &path) {
    this->path = path;
}

void Enemy::areaHit(std::vector<std::unique_ptr<Enemy>> &targets) {

}
