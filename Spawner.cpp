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

const std::vector<std::unique_ptr<Enemy>> & Spawner::getBosses() const {
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
                                       calculatePosFromTile(spawnTile))); //TODO add random spawn (only for debug)
}

void Spawner::spawnCoin(sf::Vector2f spawnPos, int value) {
    bonuses.emplace_back(new Coin(bonusesTextures.getTextureRef("coin"),
                                  spawnPos, value)); //TODO add random spawn (only for debug)

    bonusTypeSpawnedInARound[COINS] = true;
}

void Spawner::drawEnemies(sf::RenderWindow &window, bool gameOver, float dt) {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->drawEntity(window, gameOver);
        if (enemies[i]->weapon && !enemies[i]->isDead()) {
            enemies[i]->weapon->drawWeapon(window);
            enemies[i]->weapon->drawBullets(window, dt);
        }
    }
}

void Spawner::updateSkinDirection(const sf::Vector2f &target) {
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->characterSkinDirection(target);
}

void Spawner::spawnNuke(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new Nuke(bonusesTextures.getTextureRef("bonusesBox"),
                                  calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[NUKE] = true;
}

void Spawner::updateEnemy(const GameCharacter &target, float dt, int enemyIndex, bool collide,
                          const sf::RectangleShape &obstacle) {

    if (!enemies[enemyIndex]->isDead()) {

        sf::Vector2f normalizedVector, actualTarget = target.getSpriteCenter();

        //FIXME clean code
        if (!enemies[enemyIndex]->path.empty() && enemies[enemyIndex]->isPathReady())
            enemies[enemyIndex]->followPath(dt, tileSize, enemies);
        else
            enemies[enemyIndex]->move(
                    enemies[enemyIndex]->normalize(characterPositionRelativeToAnother(*enemies[enemyIndex], target)),
                    dt); //FIXME

        if ((!enemies[enemyIndex]->getSprite().getGlobalBounds().intersects(target.getSprite().getGlobalBounds()))) {

            //sf::Vector2f targetTranslatedPos = characterPositionRelativeToAnother(*enemies[enemyIndex], target);
            std::vector<Node> newPath;
            //if (collide) {
            if ((enemies[enemyIndex]->pathClock.getElapsedTime() >= enemies[enemyIndex]->updatingPathTime) ||
                enemies[enemyIndex]->firstTime) {
                enemies[enemyIndex]->firstTime = false;
                enemies[enemyIndex]->hasPath = true;

/*
                newPath = enemies[enemyIndex]->ai.findPath(calculateTileFromPos(enemies[enemyIndex]->getSpriteCenter()),
                                                           calculateTileFromPos(target.getSpriteCenter()));
                                                           */
                enemies[enemyIndex]->startPathfindingThread(calculateTileFromPos(enemies[enemyIndex]->getSpriteCenter()),
                                                            calculateTileFromPos(target.getSpriteCenter()));
                //enemies[enemyIndex]->setPath(newPath);
                enemies[enemyIndex]->pathClock.restart();
            }
            /*
        }
        else
        {

            if (enemies[enemyIndex]->hasPath )
                enemies[enemyIndex]->path.clear();

            sf::Vector2f targetTranslatedPos = characterPositionRelativeToAnother(*enemies[enemyIndex], target);
            normalizedVector = enemies[enemyIndex]->normalize(targetTranslatedPos);
        }
             */





            //enemies[enemyIndex]->calculateEnemyMoveDirectionArray(targetTranslatedPos);

            /*

            if (collide) {
                changeDirection(enemyIndex, obstacle);

                enemies[enemyIndex]->calculateDirectionVector();
                normalizedVector = enemies[enemyIndex]->direction_vector;
            } else
                normalizedVector = enemies[enemyIndex]->normalize(targetTranslatedPos);
                */



            //enemies[enemyIndex]->move(normalizedVector, dt); //move enemy (in each case)

            enemies[enemyIndex]->characterSkinDirection(target.getSpriteCenter());

        } else
            enemies[enemyIndex]->currentAnimation.update(dt); //enemies must be moving forever

        //enemies[enemyIndex]->characterSkinDirection(target.getSpriteCenter());
    }
}

void Spawner::spawnAmmunition(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new Ammunition(bonusesTextures.getTextureRef("bonusesBox"),
                                        calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[AMMUNITION] = true;
}

void Spawner::spawnLifePoints(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new LifePoints(bonusesTextures.getTextureRef("bonusesBox"),
                                        calculatePosFromTile(spawnTile), 0));

    bonusTypeSpawnedInARound[LIFE_POINTS] = true;
}

void Spawner::spawnBubble(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new ProtectionBubble(bonusesTextures.getTextureRef("bonusesBox"),
                                              calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[PROTECTION_BUBBLE] = true;
}

void Spawner::spawnArmor(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new Armor(bonusesTextures.getTextureRef("bonusesBox"),
                                   calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[ARMOR] = true;
}

void Spawner::spawnIncreasedDamage(sf::Vector2i spawnTile) {
    bonuses.emplace_back(new IncreasedWeaponDamage(bonusesTextures.getTextureRef("bonusesBox"),
                                                   calculatePosFromTile(spawnTile)));

    bonusTypeSpawnedInARound[INCREASED_DAMAGE] = true;
}

void Spawner::spawnWarrior(sf::Vector2i spawnTile, float hitProbability, float damageMultiplier) {
    sf::Vector2f damage = {3, 5};
    damage *= damageMultiplier;

    enemies.emplace_back(
            new Warrior(enemiesTextures.getTextureRef("mike"), enemiesTextures.getTextureRef("shield"), spawnTile,
                        tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, 10, damage, nodeMap,
                        hitProbability,
                        true)); //TODO add correct texture and variable speed
}

void Spawner::spawnKamikaze(sf::Vector2i spawnTile, float damageMultiplier) {
    sf::Vector2f damage = {7, 10};
    damage *= damageMultiplier;

    enemies.emplace_back(new Kamikaze(enemiesTextures.getTextureRef("kamikaze"), spawnTile,
                                      tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY},
                                      damage, nodeMap,
                                      true)); //TODO add correct texture and variable speed
}

void Spawner::spawnArcher(sf::Vector2i spawnTile, float damageMultiplier) {
    sf::Vector2f damage = {1, 3};
    damage *= damageMultiplier;

    enemies.emplace_back(new Archer(enemiesTextures.getTextureRef("archer"), weaponsTextures.getTextureRef("bow"),
                                    weaponsTextures.getTextureRef("arrow"), spawnTile,
                                    tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, damage,
                                    nodeMap,
                                    true)); //TODO add variable speed
}

void Spawner::spawnZombie(sf::Vector2i spawnTile, float hitProbability, float damageMultiplier) {
    sf::Vector2f damage = {1, 3};
    damage *= damageMultiplier;

    enemies.emplace_back(new Zombie(enemiesTextures.getTextureRef("zombie"), spawnTile,
                                    tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY}, damage,
                                    nodeMap, hitProbability,
                                    true)); //TODO add variable speed
}

void Spawner::spawnBoss(sf::Vector2i spawnTile, float hitProbability) {
    sf::Vector2f damage = {8, 13};

    bosses.emplace_back(new Boss(enemiesTextures.getTextureRef("mike"), spawnTile,
                                 tileSize, {GameCharacterSize::spriteSizeX, GameCharacterSize::spriteSizeY},
                                 damage, nodeMap,
                                 hitProbability)); //TODO add correct texture, variable speed and variable size
}

sf::Vector2f Spawner::characterPositionRelativeToAnother(const GameCharacter &originCharacter,
                                                         const GameCharacter &targetCharacter) const {
    sf::Vector2f origin;
    sf::Vector2f translation;

    origin = originCharacter.getSpriteCenter();
    translation = targetCharacter.getSpriteCenter() - origin;

    return translation;
}

sf::Vector2f
Spawner::calculateNextNodeTarget(int enemyIndex, const sf::RectangleShape &obstacle,
                                 sf::Vector2f finalTargetPos) { //TODO remove it
    sf::Vector2f nodes[4] = {{obstacle.getGlobalBounds().left -
                              enemies[enemyIndex]->getSprite().getGlobalBounds().width / 2 - 2,
                                     obstacle.getGlobalBounds().top -
                                     enemies[enemyIndex]->getSprite().getGlobalBounds().height /
                                     2 - 2},
                             {obstacle.getGlobalBounds().left + obstacle.getGlobalBounds().width +
                              enemies[enemyIndex]->getSprite().getGlobalBounds().width / 2 +
                              1,     obstacle.getGlobalBounds().top -
                                     enemies[enemyIndex]->getSprite().getGlobalBounds().height /
                                     2 - 2},
                             {obstacle.getGlobalBounds().left + obstacle.getGlobalBounds().width +
                              enemies[enemyIndex]->getSprite().getGlobalBounds().width / 2 +
                              1,     obstacle.getGlobalBounds().top +
                                     obstacle.getGlobalBounds().height +
                                     enemies[enemyIndex]->getSprite().getGlobalBounds().height /
                                     2 + 2},
                             {obstacle.getGlobalBounds().left -
                              enemies[enemyIndex]->getSprite().getGlobalBounds().width / 2 -
                              1,     obstacle.getGlobalBounds().top +
                                     obstacle.getGlobalBounds().height +
                                     enemies[enemyIndex]->getSprite().getGlobalBounds().height /
                                     2 + 2},
    };


    double distance = std::sqrt((std::pow(nodes[0].x - enemies[enemyIndex]->getSpriteCenter().x, 2)) +
                                (std::pow(nodes[0].y - enemies[enemyIndex]->getSpriteCenter().y, 2)));
    double newDistance, min = distance;
    int index = 0;

    for (int i = 1; i < 4; i++) {
        newDistance = std::sqrt((std::pow(nodes[i].x - enemies[enemyIndex]->getSpriteCenter().x, 2)) +
                                (std::pow(nodes[i].y - enemies[enemyIndex]->getSpriteCenter().y, 2)));
        if ((newDistance < min) && (newDistance > 2)) {
            min = newDistance;
            index = i;
        }
    }
    return nodes[index];

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

void Spawner::changeDirection(int enemyIndex, const sf::RectangleShape &obstacle) {
    bool targetDirection[4];
    int directionCount = 0;

    for (int i = 0; i < 4; i++) {
        targetDirection[i] = enemies[enemyIndex]->keyStates[i]; //copy array
        if (targetDirection[i])
            directionCount++;
        enemies[enemyIndex]->keyStates[i] = false; //init array
    }

    if (directionCount > 1) {

        if (enemies[enemyIndex]->getSprite().getGlobalBounds().top +
            enemies[enemyIndex]->getSprite().getGlobalBounds().height <= obstacle.getGlobalBounds().top) {
            if (targetDirection[LEFT] && targetDirection[DOWN])
                enemies[enemyIndex]->keyStates[LEFT] = true; //go left
            else if (targetDirection[RIGHT] && targetDirection[DOWN])
                enemies[enemyIndex]->keyStates[RIGHT] = true; //go right
            else if ((targetDirection[LEFT] || targetDirection[RIGHT]) && targetDirection[UP])
                enemies[enemyIndex]->keyStates[UP] = true; //go up



        } else if (enemies[enemyIndex]->getSprite().getGlobalBounds().left >=
                   obstacle.getGlobalBounds().left + obstacle.getGlobalBounds().width) {
            if (targetDirection[LEFT] && targetDirection[DOWN])
                enemies[enemyIndex]->keyStates[DOWN] = true; //go down
            else if (targetDirection[LEFT] && targetDirection[UP])
                enemies[enemyIndex]->keyStates[UP] = true; //go up
            else if ((targetDirection[UP] || targetDirection[DOWN]) && targetDirection[RIGHT])
                enemies[enemyIndex]->keyStates[RIGHT] = true; //go right



        } else if (enemies[enemyIndex]->getSprite().getGlobalBounds().left <= obstacle.getGlobalBounds().left) {
            if (targetDirection[RIGHT] && targetDirection[DOWN])
                enemies[enemyIndex]->keyStates[DOWN] = true; //go down
            else if (targetDirection[RIGHT] && targetDirection[UP])
                enemies[enemyIndex]->keyStates[UP] = true; //go up
            else if ((targetDirection[UP] || targetDirection[DOWN]) && targetDirection[LEFT])
                enemies[enemyIndex]->keyStates[LEFT] = true; //go down



        } else if (enemies[enemyIndex]->getSprite().getGlobalBounds().top >=
                obstacle.getGlobalBounds().top + obstacle.getGlobalBounds().height) {
            if (targetDirection[RIGHT] && targetDirection[UP])
                enemies[enemyIndex]->keyStates[RIGHT] = true; //go right
            else if (targetDirection[LEFT] && targetDirection[UP])
                enemies[enemyIndex]->keyStates[LEFT] = true; //go left
            else if ((targetDirection[LEFT] || targetDirection[RIGHT]) && targetDirection[DOWN])
                enemies[enemyIndex]->keyStates[DOWN] = true; //go down
        }
    } else {

        //TODO random decision

        if (targetDirection[UP] || targetDirection[DOWN])
            enemies[enemyIndex]->keyStates[RIGHT] = true; //go right //FIXME

        if (targetDirection[LEFT] || targetDirection[RIGHT])
            enemies[enemyIndex]->keyStates[DOWN] = true; //go right //FIXME
    }
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

