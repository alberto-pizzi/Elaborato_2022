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

void Spawner::updateEnemy(const GameCharacter &target, float dt, int enemyIndex, bool collide,
                          const sf::RectangleShape &obstacle) {

    sf::Vector2f normalizedVector, actualTarget = target.getSpriteCenter();

    //TODO implement enemies collision and AI deviation

    if (!enemies[enemyIndex]->getSprite().getGlobalBounds().intersects(target.getSprite().getGlobalBounds())) {

        if (!collide) { //future collision
            if (!enemies[enemyIndex]->attachedToNodes)
                normalizedVector = enemies[enemyIndex]->normalize(
                        characterPositionRelativeToAnother(*enemies[enemyIndex], target));
            else {
                //follow node
                sf::Vector2f oldVector = straightVector(enemies[enemyIndex]->normalize(
                                                                calculateTranslation(enemies[enemyIndex]->getSpriteCenter(), actualTarget)),
                                                        enemies[enemyIndex]->getSpriteCenter());
                if (((enemies[enemyIndex]->getSpriteCenter().x >= actualTarget.x) && (oldVector.y == 0)) ||
                    ((enemies[enemyIndex]->getSpriteCenter().y >= actualTarget.y) && (oldVector.x == 0)))
                    enemies[enemyIndex]->attachedToNodes = false;
                else {
                    normalizedVector = straightVector(enemies[enemyIndex]->normalize(
                                                              calculateTranslation(enemies[enemyIndex]->getSpriteCenter(), actualTarget)),
                                                      enemies[enemyIndex]->getSpriteCenter());
                    //set 0
                }
            }
            enemies[enemyIndex]->move(normalizedVector, dt);
        } else {

            //set node target
            //if (!enemies[enemyIndex]->attachedToNodes){
            actualTarget = calculateNextNodeTarget(enemyIndex, obstacle, sf::Vector2f());
            enemies[enemyIndex]->attachedToNodes = true;
            normalizedVector = straightVector(enemies[enemyIndex]->normalize(
                                                      calculateTranslation(enemies[enemyIndex]->getSpriteCenter(), actualTarget)),
                                              enemies[enemyIndex]->getSpriteCenter());
            //}



            enemies[enemyIndex]->move(normalizedVector, dt); //move with deviations
        }
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

sf::Vector2f
Spawner::calculateNextNodeTarget(int enemyIndex, const sf::RectangleShape &obstacle, sf::Vector2f finalTargetPos) {
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
    /*
    sf::Vector2f nextNodeTarget;


    if (finalTargetPos.y > obstacle.getGlobalBounds().top + obstacle.getGlobalBounds().width){
        nextNodeTarget = nodes[1];
    }

*/
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

