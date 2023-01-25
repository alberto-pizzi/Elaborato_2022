//
// Created by alber on 10/01/2023.
//

#include "Enemy.h"

Enemy::Enemy(const sf::Texture &tex, float hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
             const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
             const std::vector<std::vector<Node>> &nodeMap, float hitProbability, float hitRange, bool animated,
             unsigned int coins, float armor) : GameCharacter(tex, hp, speed,
                                                              points,
                                                              tilePosition,
                                                              tileSize,
                                                              rectSkin,
                                                              characterType,
                                                              damageHit,
                                                              hitRange,
                                                              animated, coins,
                                                              armor),
                                                nodeMap(nodeMap), hitProbability(hitProbability) {
    if (hitProbability >= 100)
        this->hitProbability = 100;
    //this->sprite.setScale(sf::Vector2f(1,1));

}

bool Enemy::isPositionOccupied(sf::Vector2f pos, const std::vector<std::unique_ptr<Enemy>> &enemies) {
    for (const auto &e: enemies) {
        if (e.get() == this) // skip itself
            continue;

        if (e->getSprite().getGlobalBounds().contains(pos))
            return true;
    }
    return false;
}

void Enemy::followPath(float dt, sf::Vector2i tileSize, const std::vector<std::unique_ptr<Enemy>> &enemies) {

    //if (!isFollowingPath) return;

    if (!path.empty()) {
        sf::Vector2f currentPos = getSpriteCenter();
        Node nextNode = path[0];
        sf::Vector2f nextPos = {static_cast<float>(nextNode.getTile().x * tileSize.x +
                                                   (sprite.getGlobalBounds().width - tileSize.x + 4)),
                                static_cast<float>(nextNode.getTile().y * tileSize.y +
                                                   (sprite.getGlobalBounds().height - tileSize.y + 4))};
        sf::Vector2f offset = nextPos - currentPos;
        sf::Vector2f normalizedVector = normalize(offset);

        // If the next position is occupied, don't move the enemy
        if (isPositionOccupied(nextPos, enemies))
            return;

        this->move(normalizedVector, dt);

        if (sprite.getGlobalBounds().contains(nextPos))
            path.erase(path.begin());
    }

    if (path.empty())
        hasPath = false;
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

bool Enemy::isAbleToHit(const GameCharacter &target, const Dice &hitDice, float hitChance) {
    sf::FloatRect hitBox = {this->getPos().left - hitRange, this->getPos().top - hitRange,
                            this->getPos().width + hitRange, this->getPos().height + hitRange};

    if ((hitClock.getElapsedTime() >= nextHitTime) && (hitBox.intersects(target.getPos()))) {
        hitClock.restart();
        if (hitChance < hitProbability)
            return true;
        else
            return false;
    } else
        return false;
}

void Enemy::hit(GameCharacter &target, std::vector<std::unique_ptr<Enemy>> &targetEnemies) {
    target.setIsHit(true);
    target.receiveDamage(static_cast<float>(randomDice.casualNumber(static_cast<int>(this->getDamageHit().x),
                                                                    static_cast<int>(this->getDamageHit().y))));
    target.hitColorClock.restart();
}

float Enemy::distanceToObstacle(sf::Vector2f position, const sf::RectangleShape &obstacle) {
    return std::sqrt((position.x - obstacle.getPosition().x) * (position.x - obstacle.getPosition().x) +
                     (position.y - obstacle.getPosition().y) * (position.y - obstacle.getPosition().y));
}

sf::Vector2f Enemy::getPathReferencePoint(sf::Vector2i tileSize) const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    Node nextNode = path[0];
    sf::Vector2f nextPos = {static_cast<float>(nextNode.getTile().x * tileSize.x),
                            static_cast<float>(nextNode.getTile().y * tileSize.y)};
    sf::Vector2f reference = {bounds.left + bounds.width / 2, bounds.top + bounds.height};
    sf::Vector2f offset = nextPos - reference;
    if (std::abs(offset.x) > std::abs(offset.y))
        reference.x = bounds.left + (offset.x > 0 ? bounds.width : 0);
    else
        reference.y = bounds.top + (offset.y > 0 ? bounds.height : 0);
    return reference;
}

float Enemy::length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

bool Enemy::isColliding1() const {
    return isColliding;
}

void Enemy::setIsColliding(bool isColliding) {
    Enemy::isColliding = isColliding;
}

void Enemy::updateCharacterColor() {
    if (isHit) {
        sprite.setColor(hitColor);
        if (hitColorClock.getElapsedTime() >= hitTimeColor)
            isHit = false;
    } else {
        sprite.setColor(sf::Color::White);
        if (weapon != nullptr)
            weapon->weaponSprite.setColor(sf::Color::White);
    }
}

void Enemy::receiveDamage(float damagePoints) {
    if (armor > 0) {
        damagePoints = damageWithArmor(damagePoints);
        armor--;
    }
    HP -= damagePoints;
}

