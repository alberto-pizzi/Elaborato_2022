//
// Created by alber on 10/01/2023.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Texture &tex, float hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
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
                            nodeMap(nodeMap) {

}

void Enemy::followPath(float dt, sf::Vector2i tileSize) {

    if (!path.empty()) {

        sf::Vector2f currentPos = getSpriteCenter();

        Node nextNode = path[0]; //first node
        //FIXME diagonal collision movement
        sf::Vector2f nextPos = {static_cast<float>(nextNode.getTile().x * tileSize.x),
                                static_cast<float>(nextNode.getTile().y * tileSize.y)};
        sf::Vector2f offset = nextPos - currentPos;
        sf::Vector2f normalizedVector = normalize(offset);

        this->move(normalizedVector, dt);

        if (sprite.getGlobalBounds().contains(nextPos))
            path.erase(path.begin());
    }

    if (path.empty())
        hasPath = false;

}

void Enemy::areaHit(std::vector<std::unique_ptr<Enemy>> &targets) {

}

void Enemy::setPath(const std::vector<Node> &path) {
    this->path = path;
}

void Enemy::startPathfindingThread(sf::Vector2i startTile, sf::Vector2i targetTile) {
    ai = std::make_shared<AI>(nodeMap);
    pathReady = false;
    pathfindingThread = std::thread(&Enemy::findPathWrapper, ai, startTile, targetTile, std::ref(path),
                                    std::ref(pathReady));
    pathfindingThread.detach();
}

void Enemy::findPathWrapper(const std::shared_ptr<AI> &ai, sf::Vector2i startTile, sf::Vector2i targetTile,
                            std::vector<Node> &path,
                            std::atomic<bool> &pathReady) {
    path = ai->findPath(startTile, targetTile);
    pathReady = true;
}

bool Enemy::isPathReady() {
    return pathReady;
}
