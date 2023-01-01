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

void Spawner::spawnEnemies(sf::Vector2i spawnTile) {
    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), spawnTile,
                                    {32, 32}, {32, 32},
                                    true)); //TODO add random spawn (only for debug), correct texture and variable speed

    /*
//TODO remove them
enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), {36, 27},
    {32, 32}, {32, 32},
    true));
enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("mike"), {40, 25},
    {32, 32}, {32, 32},
    true));


enemies.emplace_back(
new Warrior(enemiesTextures.getTextureRef("mike"), enemiesTextures.getTextureRef("shield"), {40, 25},
{32, 32}, {32, 32}, 10,
true));
*/

}

void Spawner::drawEnemies(sf::RenderWindow &window) {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->drawEntity(window);
}

void Spawner::updateSkinDirection(const sf::Vector2f &target) {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->characterSkinDirection(target);
}

void Spawner::spawnNuke() {
    bonuses.emplace_back(new Nuke(bonusesTextures.getTextureRef("bonusesBox"),
                                  {36 * 32, 15 * 32})); //TODO set random tile
}

void Spawner::updateEnemies(const GameCharacter &target, float dt, int enemyIndex) {
    sf::Vector2f origin;
    sf::Vector2f translation;

    origin = enemies[enemyIndex]->getSpriteCenter();
    translation = target.getSpriteCenter() - origin;
    enemies[enemyIndex]->move(enemies[enemyIndex]->normalize(translation), dt);
    enemies[enemyIndex]->currentAnimation.update(dt);
}

void Spawner::spawnAmmunition() {
    bonuses.emplace_back(new Ammunition(bonusesTextures.getTextureRef("bonusesBox"),
                                        {36 * 32, 15 * 32})); //TODO set  random tile
}

void Spawner::spawnLifePoints() {
    bonuses.emplace_back(new LifePoints(bonusesTextures.getTextureRef("bonusesBox"),
                                        {36 * 32, 15 * 32})); //TODO set random tile
}

void Spawner::spawnBubble() {
    bonuses.emplace_back(new ProtectionBubble(bonusesTextures.getTextureRef("bonusesBox"),
                                              {36 * 32, 15 * 32})); //TODO set  random tile
}

void Spawner::spawnArmor() {
    bonuses.emplace_back(new Armor(bonusesTextures.getTextureRef("bonusesBox"),
                                   {36 * 32, 15 * 32})); //TODO  set random tile
}

void Spawner::spawnIncreasedDamage() {
    bonuses.emplace_back(new IncreasedWeaponDamage(bonusesTextures.getTextureRef("bonusesBox"),
                                                   {36 * 32, 15 * 32})); //TODO set crandom tile

}

