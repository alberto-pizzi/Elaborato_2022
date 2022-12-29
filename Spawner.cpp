//
// Created by alber on 12/11/2022.
//

#include "Spawner.h"

const std::vector<std::unique_ptr<GameCharacter>> &Spawner::getEnemies() const {
    return enemies;
}

const std::vector<std::unique_ptr<Bonus>> &Spawner::getBonuses() const {
    return bonuses;
}

const std::vector<std::unique_ptr<GameCharacter>> &Spawner::getBosses() const {
    return bosses;
}

Spawner::Spawner(const TextureManager &enemiesTextures, const TextureManager &bonusesTextures,
                 const TextureManager &weaponsTextures) {
    this->enemiesTextures = enemiesTextures;
    this->bonusesTextures = bonusesTextures;
    this->weaponsTextures = weaponsTextures;
}

void Spawner::despawnBonus(int bonusIndex) {
    bonuses.erase(bonuses.begin() + bonusIndex);
}

void Spawner::drawBonuses(sf::RenderWindow &window) const {
    for (int i = 0; i < bonuses.size(); i++)
        bonuses[i]->drawBonus(window);
}

void Spawner::spawnWeapon() {
    bonuses.emplace_back(new NewWeapon(weaponsTextures, bonusesTextures.getTextureRef("weaponBox"),
                                       {40 * 32, 24 * 32})); //TODO add random spawn (only for debug)
}

void Spawner::spawnCoin() {
    bonuses.emplace_back(new Coin(bonusesTextures.getTextureRef("coin"),
                                  {36 * 32, 24 * 32})); //TODO add random spawn (only for debug)
}

void Spawner::spawnEnemies() {
    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), {36, 24},
                                    {32, 32}, {32, 32},
                                    true)); //TODO add random spawn (only for debug) and correct texture
    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), {36, 27},
                                    {32, 32}, {32, 32},
                                    true));
    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), {40, 25},
                                    {32, 32}, {32, 32},
                                    true));
}

void Spawner::drawEnemies(sf::RenderWindow &window) {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->drawEntity(window);
}

void Spawner::updateSkinDirection(const sf::Vector2f &target) {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->enemySkinDirection(target);
}

void Spawner::spawnNuke() {
    bonuses.emplace_back(new Nuke(bonusesTextures.getTextureRef("coin"),
                                  {36 * 32, 15 * 32}));
}

