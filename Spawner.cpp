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

void Spawner::updateEnemy(const GameCharacter &target, float dt, int enemyIndex, bool collide) {

    sf::Vector2f normalizedVector = enemies[enemyIndex]->normalize(
            characterPositionRelativeToAnother(*enemies[enemyIndex], target));

    //TODO implement enemies collision and AI deviation

    if (!enemies[enemyIndex]->getSprite().getGlobalBounds().intersects(target.getSprite().getGlobalBounds())) {
        /*
        if (!collide) {
            if (findCollideTile) {
                enemies[enemyIndex]->move(wantedDirection, dt);
                findCollideTile = false;
            }
            else
                enemies[enemyIndex]->move(normalizedVector, dt);
        }
        else{
            wantedDirection = normalizedVector; //save wanted direction for using it later
            //TODO implement random  decision (0,1)

            if (wantedDirection.y > 0){ //if he go down, he will go to right
                normalizedVector.x = -wantedDirection.x; //go right
                normalizedVector.y = 0;
                findCollideTile = true;
            }

            if (wantedDirection.x < 0){ //if he go down, he will go to right
                normalizedVector.y = wantedDirection.y; //go down
                normalizedVector.x = 0;
                findCollideTile = true;
            }


            */



        enemies[enemyIndex]->move(normalizedVector, dt); //move with deviations
        //}
        enemies[enemyIndex]->characterSkinDirection(target.getSpriteCenter());
    } else
        enemies[enemyIndex]->currentAnimation.update(dt); //enemies must be moving forever

    //enemies[enemyIndex]->characterSkinDirection(target.getSpriteCenter());
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

sf::Vector2f Spawner::characterPositionRelativeToAnother(const GameCharacter &originCharacter,
                                                         const GameCharacter &targetCharacter) const {
    sf::Vector2f origin;
    sf::Vector2f translation;

    origin = originCharacter.getSpriteCenter();
    translation = targetCharacter.getSpriteCenter() - origin;

    return translation;
}

