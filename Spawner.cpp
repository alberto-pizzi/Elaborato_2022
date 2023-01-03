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

void Spawner::spawnWeapon(sf::Vector2f spawnPos) {
    bonuses.emplace_back(new NewWeapon(weaponsTextures, bonusesTextures.getTextureRef("weaponBox"),
                                       {40 * 32, 24 * 32})); //TODO add random spawn (only for debug)
}

void Spawner::spawnCoin(sf::Vector2f spawnPos) {
    bonuses.emplace_back(new Coin(bonusesTextures.getTextureRef("coin"),
                                  {36 * 32, 24 * 32})); //TODO add random spawn (only for debug)
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
    if (!enemies[enemyIndex]->getSprite().getGlobalBounds().intersects(target.getSprite().getGlobalBounds()))
        enemies[enemyIndex]->move(enemies[enemyIndex]->normalize(translation), dt);
    else
        enemies[enemyIndex]->currentAnimation.update(dt); //enemies must be moving forever
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

void Spawner::spawnWarrior(sf::Vector2i spawnTile) {
    sf::Vector2f damage = {3, 5};

    enemies.emplace_back(
            new Warrior(enemiesTextures.getTextureRef("mike"), enemiesTextures.getTextureRef("shield"), spawnTile,
                        {32, 32}, {32, 32}, 10, damage,
                        true)); //TODO add correct texture and variable speed
}

void Spawner::spawnKamikaze(sf::Vector2i spawnTile) {
    sf::Vector2f damage = {7, 10};

    enemies.emplace_back(new Kamikaze(enemiesTextures.getTextureRef("mike"), spawnTile,
                                      {32, 32}, {32, 32}, damage,
                                      true)); //TODO add correct texture and variable speed
}

void Spawner::spawnArcher(sf::Vector2i spawnTile) {
    //TODO add archer
}

void Spawner::spawnZombie(sf::Vector2i spawnTile) {
    sf::Vector2f damage = {1, 3};

    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("zombie"), spawnTile,
                                    {32, 32}, {32, 32}, damage,
                                    true)); //TODO add variable speed
}

void Spawner::spawnBoss(sf::Vector2i spawnTile) {
    sf::Vector2f damage = {8, 13};

    bosses.emplace_back(new Boss(enemiesTextures.getTextureRef("mike"), spawnTile,
                                 {32, 32}, {32, 32},
                                 damage)); //TODO add correct texture, variable speed and variable size
}

