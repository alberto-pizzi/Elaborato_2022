//
// Created by alber on 12/11/2022.
//

#ifndef ELABORATO_SPAWNER_H
#define ELABORATO_SPAWNER_H

#include <memory>
#include <vector>
#include <iostream>

#include "GameCharacter.h"
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


class Spawner {
private:
    friend class PlayState;

    std::vector<std::unique_ptr<GameCharacter>> enemies;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    std::vector<std::unique_ptr<GameCharacter>> bosses;
    TextureManager enemiesTextures;
    TextureManager bonusesTextures;
    TextureManager weaponsTextures;
public:
    Spawner(const TextureManager &enemiesTextures, const TextureManager &bonusesTextures,
            const TextureManager &weaponsTextures);

    const std::vector<std::unique_ptr<GameCharacter>> &getEnemies() const;

    const std::vector<std::unique_ptr<Bonus>> &getBonuses() const;

    const std::vector<std::unique_ptr<GameCharacter>> &getBosses() const;

    void spawnWeapon(sf::Vector2f spawnPos);

    void despawnBonus(int bonusIndex);

    void drawBonuses(sf::RenderWindow &window) const;

    void drawEnemies(sf::RenderWindow &window);

    void updateSkinDirection(const sf::Vector2f &target);

    void updateEnemies(const GameCharacter &target, float dt, int enemyIndex);

    void spawnCoin(sf::Vector2f spawnPos);

    void spawnNuke();

    void spawnAmmunition();

    void spawnLifePoints();

    void spawnBubble();

    void spawnArmor();

    void spawnIncreasedDamage();

    void spawnZombie(sf::Vector2i spawnTile);

    void spawnArcher(sf::Vector2i spawnTile);

    void spawnKamikaze(sf::Vector2i spawnTile);

    void spawnWarrior(sf::Vector2i spawnTile);

    void spawnBoss(sf::Vector2i spawnTile);

};


#endif //ELABORATO_SPAWNER_H
