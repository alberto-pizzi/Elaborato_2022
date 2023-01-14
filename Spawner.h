//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_SPAWNER_H
#define ELABORATO_SPAWNER_H

#include <memory>
#include <vector>
#include <iostream>

#include "Bonus.h"
#include "NewWeapon.h"
#include "TextureManager.h"
#include "Coin.h"
#include "Zombie.h"
#include "Nuke.h"
#include "Ammunition.h"
#include "LifePoints.h"
#include "ProtectionBubble.h"
#include "Armor.h"
#include "IncreasedWeaponDamage.h"
#include "Warrior.h"
#include "Kamikaze.h"
#include "Boss.h"
#include "Enemy.h"
#include "Archer.h"


class Spawner {
private:
    friend class PlayState;

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<std::unique_ptr<Enemy>> bosses;
    TextureManager enemiesTextures;
    TextureManager bonusesTextures;
    TextureManager weaponsTextures;

    //enemies update
    sf::Vector2f wantedDirection;
    bool findCollideTile = false;

    //node map
    std::vector<std::vector<Node>> nodeMap;
    sf::Vector2i tileSize;
public:
    Spawner(const TextureManager &enemiesTextures, const TextureManager &bonusesTextures,
            const TextureManager &weaponsTextures, const std::vector<std::vector<Node>> &nodeMap,
            sf::Vector2i tileSize);

    const std::vector<std::unique_ptr<Enemy>> & getEnemies() const;

    const std::vector<std::unique_ptr<Bonus>> &getBonuses() const;

    const std::vector<std::unique_ptr<Enemy>> & getBosses() const;

    void spawnWeapon(sf::Vector2f spawnPos);

    void despawnBonus(int bonusIndex);

    void drawBonuses(sf::RenderWindow &window) const;

    void drawEnemies(sf::RenderWindow &window, bool gameOver, float dt);

    void updateSkinDirection(const sf::Vector2f &target);

    void updateEnemy(const GameCharacter &target, float dt, int enemyIndex, bool collide,
                     const sf::RectangleShape &obstacle);

    void spawnCoin(sf::Vector2f spawnPos, int value);

    void spawnNuke();

    void spawnAmmunition();

    void spawnLifePoints();

    void despawnEnemy(int &enemyIndex, unsigned int &remainEnemies);

    void spawnBubble();

    void spawnArmor();

    void spawnIncreasedDamage();

    void spawnZombie(sf::Vector2i spawnTile);

    void spawnArcher(sf::Vector2i spawnTile);

    void spawnKamikaze(sf::Vector2i spawnTile);

    void spawnWarrior(sf::Vector2i spawnTile);

    void spawnBoss(sf::Vector2i spawnTile);

    sf::Vector2f characterPositionRelativeToAnother(const GameCharacter &originCharacter,
                                                    const GameCharacter &targetCharacter) const;

    sf::Vector2f
    calculateNextNodeTarget(int enemyIndex, const sf::RectangleShape &obstacle, sf::Vector2f finalTargetPos);

    sf::Vector2f calculateTranslation(sf::Vector2f origin, sf::Vector2f target) const;

    sf::Vector2f straightVector(sf::Vector2f actualTargetPos, sf::Vector2f actualCharacterPos);

    void changeDirection(int enemyIndex, const sf::RectangleShape &obstacle);

    sf::Vector2i calculateTileFromPos(sf::Vector2f pos) const;

    sf::Vector2f calculatePosFromTile(sf::Vector2i tile) const;


};


#endif //ELABORATO_SPAWNER_H
