//
// Created by alber on 12/11/2022.
//

#include "Spawner.h"

const std::vector<std::unique_ptr<Enemy>> & Spawner::getEnemies() const {
    return enemies;
}

const std::vector<std::unique_ptr<Bonus>> &Spawner::getBonuses() const {
    return bonuses;
}

const std::vector<std::unique_ptr<Boss>> &Spawner::getBosses() const {
    return bosses;
}

Spawner::Spawner(const TextureManager &enemiesTextures, const TextureManager &bonusesTextures,
                 const TextureManager &weaponsTextures, const std::vector<std::vector<Node>> &nodeMap,
                 sf::Vector2i tileSize) {
    this->enemiesTextures = enemiesTextures;
    this->bonusesTextures = bonusesTextures;
    this->weaponsTextures = weaponsTextures;
    this->nodeMap = nodeMap;
    this->tileSize = tileSize;
}

void Spawner::despawnBonus(int bonusIndex) {
    bonuses.erase(bonuses.begin() + bonusIndex);
}

void Spawner::drawBonuses(sf::RenderWindow &window) const {
    for (int i = 0; i < bonuses.size(); i++)
        bonuses[i]->drawBonus(window);
}

void Spawner::spawnWeapon(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new NewWeapon(weaponsTextures, bonusesTextures.getTextureRef("weaponBox"),
                                       calculatePosFromTile(spawnTile), chanceDice));
}

void Spawner::spawnCoin(sf::Vector2f spawnPos, int value) {
    bonuses.emplace_back(new Coin(bonusesTextures.getTextureRef("coin"),
                                  spawnPos, value));

    bonusTypeSpawnedInARound[COINS] = true;
}

void Spawner::drawEnemies(sf::RenderWindow &window, float dt) {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->drawEntity(window);
        if (enemies[i]->weapon && !enemies[i]->isDead()) {
            //enemies[i]->weapon->drawWeapon(window);
            enemies[i]->weapon->drawBullets(window, dt);
        }
    }
    for (int i = 0; i < bosses.size(); i++) {
        bosses[i]->drawEntity(window);
        if (bosses[i]->weapon && !bosses[i]->isDead()) {
            //bosses[i]->weapon->drawWeapon(window);
            bosses[i]->weapon->drawBullets(window, dt);
        }
    }
}

void Spawner::spawnNuke(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new Nuke(bonusesTextures.getTextureRef("bonusesBox"),
                                  calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[NUKE] = true;
}

void Spawner::updateEnemyPos(const GameCharacter &target, float dt, int enemyIndex,
                             const std::vector<sf::RectangleShape> &walls, sf::FloatRect futurePos) {

    if (!enemies[enemyIndex]->isDead()) {

        sf::Vector2f normalizedVector, actualTarget = target.getSpriteCenter();

        //check map collision
        bool collision = false;

        for (int i = 0; i < walls.size(); i++) {
            if (futurePos.intersects(walls[i].getGlobalBounds())) {
                collision = true;
                break;
            }
        }

        if ((!enemies[enemyIndex]->getSprite().getGlobalBounds().intersects(target.getSprite().getGlobalBounds()))) {

            //find new path
            if ((enemies[enemyIndex]->pathClock.getElapsedTime() >= enemies[enemyIndex]->updatingPathTime) ||
                enemies[enemyIndex]->firstTime) {
                enemies[enemyIndex]->firstTime = false;
                enemies[enemyIndex]->hasPath = true;

                // generate a new path for the enemy
                enemies[enemyIndex]->startPathfindingThread(
                        calculateTileFromPos(enemies[enemyIndex]->getSpriteCenter()),
                        calculateTileFromPos(target.getSpriteCenter()));
                enemies[enemyIndex]->pathClock.restart();
            }
        }

        //after some time set the movement to free movement (not path)
        if ((enemies[enemyIndex]->followPathClock.getElapsedTime() >= enemies[enemyIndex]->followPathOffset) &&
            !collision) {
            enemies[enemyIndex]->setIsColliding(false);
            enemies[enemyIndex]->followPathClock.restart();
        }

        // check if enemy is colliding with an obstacle
        if (collision || enemies[enemyIndex]->isColliding1()) {
            // check if the enemy has a path ready to follow
            if (!enemies[enemyIndex]->path.empty() && enemies[enemyIndex]->isPathReady()) {
                // follow the path generated by A*
                enemies[enemyIndex]->followPath(dt, tileSize, enemies);
            }
            enemies[enemyIndex]->setIsColliding(true);

        } else {
            enemies[enemyIndex]->setIsColliding(false);
            // if the enemy is not colliding with the target, generate a new path

            // move the enemy in a straight line towards the target
            enemies[enemyIndex]->move(
                    enemies[enemyIndex]->normalize(characterPositionRelativeToAnother(*enemies[enemyIndex], target)),
                    dt);

            enemies[enemyIndex]->characterSkinDirection(target.getSpriteCenter());
        }
    } else
        enemies[enemyIndex]->currentAnimation.update(dt); //enemies must be moving forever
}

void Spawner::spawnAmmunition(sf::Vector2i spawnTile) {
    //these values are unique, so if you want change them you can do it without problems
    //casual ammo quantity (change follow line is you want to change min e max values)
    int quantity = chanceDice.casualNumber(5, 40);

    bonuses.emplace_back(new Ammunition(bonusesTextures.getTextureRef("bonusesBox"),
                                        calculatePosFromTile(spawnTile), quantity));

    bonusTypeSpawnedInARound[AMMUNITION] = true;
}

void Spawner::spawnLifePoints(sf::Vector2i spawnTile) {
    //these values are unique, so if you want change them you can do it without problems
    //casual life points quantity (change follow line is you want to change min e max values)
    float quantity = static_cast<float>(chanceDice.casualNumber(1, 8));

    bonuses.emplace_back(new LifePoints(bonusesTextures.getTextureRef("bonusesBox"),
                                        calculatePosFromTile(spawnTile), quantity));

    bonusTypeSpawnedInARound[LIFE_POINTS] = true;
}

void Spawner::spawnBubble(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new ProtectionBubble(bonusesTextures.getTextureRef("bonusesBox"),
                                              calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[PROTECTION_BUBBLE] = true;
}

void Spawner::spawnArmor(sf::Vector2i spawnTile) {
    //these values are unique, so if you want change them you can do it without problems
    //casual armor quantity (change follow line is you want to change min e max values)
    float quantity = static_cast<float>(chanceDice.casualNumber(3, 15));

    bonuses.emplace_back(new Armor(bonusesTextures.getTextureRef("bonusesBox"),
                                   calculatePosFromTile(spawnTile), quantity));

    bonusTypeSpawnedInARound[ARMOR] = true;
}

void Spawner::spawnIncreasedDamage(sf::Vector2i spawnTile) {
    //these values are unique, so if you want change them you can do it without problems
    //casual multiplier (change follow line is you want to change min e max values)
    float multiplier = static_cast<float>(chanceDice.casualNumber(12, 25));
    multiplier /= 10; //from 1.2 to 2.5

    bonuses.emplace_back(new IncreasedWeaponDamage(bonusesTextures.getTextureRef("bonusesBox"),
                                                   calculatePosFromTile(spawnTile), multiplier));

    bonusTypeSpawnedInARound[INCREASED_DAMAGE] = true;
}

void Spawner::spawnWarrior(sf::Vector2i spawnTile, float hitProbability, float damageMultiplier) {
    //these values are unique, so if you want change them you can do it without problems
    sf::Vector2f damage = {3, 5};
    damage *= damageMultiplier;

    //casual defense value (change follow line is you want to change min e max values)
    float defense = static_cast<float>(chanceDice.casualNumber(5, 40));

    enemies.emplace_back(
            new Warrior(enemiesTextures.getTextureRef("unshieldedWarrior"),
                        enemiesTextures.getTextureRef("shieldedWarrior"), spawnTile,
                        tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, defense, damage,
                        nodeMap,
                        hitProbability,
                        true));
}

void Spawner::spawnKamikaze(sf::Vector2i spawnTile, float damageMultiplier) {
    //these values are unique, so if you want change them you can do it without problems
    sf::Vector2f damage = {7, 10};
    damage *= damageMultiplier;

    enemies.emplace_back(new Kamikaze(enemiesTextures.getTextureRef("kamikaze"), spawnTile,
                                      tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY},
                                      damage, nodeMap,
                                      true));
}

void Spawner::spawnArcher(sf::Vector2i spawnTile, float damageMultiplier) {
    //these values are unique, so if you want change them you can do it without problems
    sf::Vector2f damage = {1, 3};
    damage *= damageMultiplier;

    enemies.emplace_back(new Archer(enemiesTextures.getTextureRef("archer"), weaponsTextures.getTextureRef("bow"),
                                    weaponsTextures.getTextureRef("arrow"), spawnTile,
                                    tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, damage,
                                    nodeMap,
                                    true));
}

void Spawner::spawnZombie(sf::Vector2i spawnTile, float hitProbability, float damageMultiplier) {
    //these values are unique, so if you want change them you can do it without problems
    sf::Vector2f damage = {1, 3};
    damage *= damageMultiplier;

    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("zombie"), spawnTile,
                                    tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, damage,
                                    nodeMap, hitProbability,
                                    true));
}

void Spawner::spawnBoss(sf::Vector2i spawnTile, float damageMultiplier) {
    //these values are unique, so if you want change them you can do it without problems
    sf::Vector2f damage = {8, 13};
    damage *= damageMultiplier;

    bosses.emplace_back(new Boss(enemiesTextures.getTextureRef("boss"), weaponsTextures.getTextureRef("scepter"),
                                 weaponsTextures.getTextureRef("energy"), spawnTile,
                                 tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY},
                                 damage));
}

sf::Vector2f Spawner::characterPositionRelativeToAnother(const GameCharacter &originCharacter,
                                                         const GameCharacter &targetCharacter) const {
    sf::Vector2f origin;
    sf::Vector2f translation;

    origin = originCharacter.getSpriteCenter();
    translation = targetCharacter.getSpriteCenter() - origin;

    return translation;
}

sf::Vector2f Spawner::calculateTranslation(sf::Vector2f origin, sf::Vector2f target) const {
    sf::Vector2f translation;
    translation = target - origin;
    return translation;
}

sf::Vector2f Spawner::straightVector(sf::Vector2f actualTargetPos, sf::Vector2f actualCharacterPos) {
    sf::Vector2f modifiedVector, permanentVector = actualTargetPos;

    if ((actualTargetPos.x > actualCharacterPos.x) ||
        (actualTargetPos.x < actualCharacterPos.x)) //actual target is on right
        modifiedVector = {permanentVector.x, 0};
    else if ((actualTargetPos.y > actualCharacterPos.y) || (actualTargetPos.y < actualCharacterPos.y))
        modifiedVector = {0, permanentVector.y};

    return modifiedVector;

}

sf::Vector2i Spawner::calculateTileFromPos(sf::Vector2f pos) const {
    return {static_cast<int>(pos.x) / tileSize.x, static_cast<int>(pos.y) / tileSize.y};
}

sf::Vector2f Spawner::calculatePosFromTile(sf::Vector2i tile) const {
    return {static_cast<float>(tile.x * tileSize.x), static_cast<float>(tile.y * tileSize.y)};
}

void Spawner::despawnEnemy(int &enemyIndex, unsigned int &remainEnemies) {
    enemies.erase(enemies.begin() + enemyIndex);
    enemyIndex--;
    remainEnemies--;
}

void Spawner::despawnAllEnemies() {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->setHp(0);
}

float Spawner::calculateChance(const Dice &dice) const {
    int chance = dice.casualNumber(0, 100);
    return static_cast<float>(chance);
}

bool Spawner::isAbleToSpawn(const Dice &dice, float spawnChance, float spawnProbability) const {
    if (spawnChance < spawnProbability)
        return true;
    else
        return false;
}

void
Spawner::updateBossPos(const GameCharacter &target, float dt, int bossIndex,
                       const std::vector<sf::RectangleShape> &walls,
                       sf::FloatRect futurePos) {

    if (!bosses[bossIndex]->isDead()) {

        //check map collision
        bool collision = false;

        for (int i = 0; i < walls.size(); i++) {
            if (futurePos.intersects(walls[i].getGlobalBounds())) {
                collision = true;
                break;
            }
        }

        sf::Vector2f futureSpriteCenter = {futurePos.left + futurePos.width / 2, futurePos.top + futurePos.height / 2};

        if (!collision && (bosses[bossIndex]->calculateDistanceBetweenPositions(bosses[bossIndex]->getSpawnOrigin(),
                                                                                futureSpriteCenter) <=
                           bosses[bossIndex]->getMaxMovingRange()))
            // move the enemy in a straight line towards the target
            bosses[bossIndex]->move(
                    bosses[bossIndex]->normalize(characterPositionRelativeToAnother(*bosses[bossIndex], target)),
                    dt);
        bosses[bossIndex]->characterSkinDirection(target.getSpriteCenter());

    } else
        bosses[bossIndex]->currentAnimation.update(dt); //enemies must be moving forever

}

void Spawner::despawnBoss(int &bossIndex, unsigned int &remainBosses) {
    bosses.erase(bosses.begin() + bossIndex);
    bossIndex--;
    remainBosses--;
}

