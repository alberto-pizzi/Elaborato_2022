//
// Created by alber on 12/11/2022.
//

#include "Mike.h"
#include "Bonus.h"


Mike::Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
           const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, float hp, float speed, float armor)
        : GameCharacter(mikeTexture, hp,
                        speed,
                        0,
                        spawnTile,
                        tileSize,
                        rectSkin, MIKE, {0, 0}, 5,
                        true,
                        0,
                        armor),
          gui(this->points, 1, 12, 12, true, startRoundCountdownSeconds, handgunTexture,
              guiTexManager) { //WARNING: Mike's damage hit never will be used

    weapon = std::unique_ptr<Weapon>(new Handgun(true, handgunTexture, handgunBulletTexture));
    gui.updateWeaponType(handgunTexture, weapon->currentAnimation.idleFrames[0], weapon->hitBox.getSize());

    sf::Font progressFont;
    std::string textFontFile = "res/fonts/arial.ttf";
    try {
        if (!progressFont.loadFromFile(textFontFile))
            throw GameException("Error opening textFontFile file", textFontFile, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    //init achievements (create instance and create each achievement)
    initAchievements(guiTexManager);
}

/*
void Mike::drawEntity(sf::RenderWindow &window) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}
*/


void Mike::addToOwnBonuses(int bonusType, sf::Time duration) {
    sf::Clock timer;
    actualBonuses.push_back({bonusType, timer, duration});
}

void Mike::updateActiveBonuses() {
    for (int i = 0; i < actualBonuses.size(); i++) {
        if (actualBonuses[i].effectTimer.getElapsedTime() >= actualBonuses[i].effectTime) {
            switch (actualBonuses[i].bonusType) {
                case BonusType::PROTECTION_BUBBLE:
                    bubble = false; //reset bubble to default value (false)
                    break;
                case BonusType::INCREASED_DAMAGE:
                    weapon->setDamageMultiplier(1); //reset damage multiplier to default value (1)
                    weapon->setDamage(weapon->getDefaultDamage());
                    break;
                default:
                    std::cerr << "ERROR: OWNABLE BONUS NOT EXIST" << std::endl;
                    break;
            }
            actualBonuses.erase(actualBonuses.begin() + i);
            i--;
        }
        if (actualBonuses.empty())
            break;
    }
}

std::vector<Mike::ActualBonus> Mike::getActualBonuses() const {
    return actualBonuses;
}

unsigned int Mike::getKills() const {
    return kills;
}

unsigned int Mike::getRoundKills() const {
    return roundKills;
}

Mike::~Mike() = default;

void Mike::registerObserver(Observer *observer) {
    observers.push_back(observer);
}

void Mike::removeObserver(Observer *observer) {
    observers.remove(observer);
}

void Mike::notifyObserver(int achievementType, unsigned int value) const {
    for (auto itr = std::begin(observers); itr != std::end(observers); itr++)
        (*itr)->update(achievementType, value);
}

void Mike::incrementKills(int enemyType) {
    enemyTypeKills[enemyType]++;
    roundKills++;
    kills++;

    //notify oberver
    notifyObserver(AchievementTypes::Kills, this->kills);

    /*
    if (enemyType == BOSS) {
        notifyObserver("Kill 2 bosses", enemyTypeKills[BOSS]);
        notifyObserver("Kill 5 bosses", enemyTypeKills[BOSS]);
        notifyObserver("Kill 10 bosses", enemyTypeKills[BOSS]);
    } else if (enemyType == KAMIKAZE) {
        notifyObserver("Kill 10 kamikaze", enemyTypeKills[KAMIKAZE]);
        notifyObserver("Kill 30 kamikaze", enemyTypeKills[KAMIKAZE]);
        notifyObserver("Kill 60 kamikaze", enemyTypeKills[KAMIKAZE]);
        notifyObserver("Kill 100 kamikaze", enemyTypeKills[KAMIKAZE]);
    }
*/

}

void Mike::resetRoundKills() {
    roundKills = 0;
}

bool Mike::isBubble() const {
    return bubble;
}

void Mike::setBubble(bool bubble) {
    Mike::bubble = bubble;
}

void Mike::updateCharacterColor() {
    if (isHit) {
        sprite.setColor(hitColor);
        if (weapon)
            weapon->weaponSprite.setColor(hitColor);
        if (hitColorClock.getElapsedTime() >= hitTimeColor)
            isHit = false;
    } else if (bubble) {
        sprite.setColor(bubbleColor);
        if (weapon)
            weapon->weaponSprite.setColor(bubbleColor);
    } else {
        sprite.setColor(sf::Color::White);
        if (weapon)
            weapon->weaponSprite.setColor(sf::Color::White);
    }
}

void Mike::receiveDamage(float damagePoints) {
    if (!bubble) {
        if (armor > 0) {
            damagePoints = damageWithArmor(damagePoints);
            armor--;
        }
        HP -= damagePoints;
    }
}

void Mike::incrementBonusCollected(int bonusType) {
    bonusTypeCollected[bonusType]++;
    bonusesCollected++;
    //TODO add observer notifier
}

void Mike::initAchievements(const TextureManager &guiTexManager) {
    AchievementManager::createInstance(this, guiTexManager);

    //kills
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 10 enemies", 10);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 150 enemies", 150);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 250 enemies", 250);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 500 enemies", 500);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 1000 enemies", 1000);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 1500 enemies", 1500);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Kills, "Kill 2000 enemies", 2000);

    //points
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Points, "Accumulate 100 points", 100);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Points, "Accumulate 500 points", 500);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Points, "Accumulate 1500 points", 1500);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Points, "Accumulate 3000 points", 3000);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Points, "Accumulate 10000 points", 10000);

    //coins
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Collect_coins, "Collect 100 coins", 100);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Collect_coins, "Collect 500 coins", 500);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Collect_coins, "Collect 1000 coins", 1000);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Collect_coins, "Collect 2000 coins", 2000);
    AchievementManager::getInstance()->createAchievement(AchievementTypes::Collect_coins, "Collect 6000 coins", 6000);

}

void Mike::setPoints(int points) {
    GameCharacter::setPoints(points);

    //notify observer
    notifyObserver(AchievementTypes::Points, this->points);

}

void Mike::setCoins(int coins) {
    GameCharacter::setCoins(coins);

    //notify observer
    notifyObserver(AchievementTypes::Collect_coins, this->coins);
}

void Mike::calculateDirectionVector() {

    if ((keyStates[LEFT] && keyStates[RIGHT]) || (!keyStates[LEFT] && !keyStates[RIGHT]))
        direction_vector.x = 0.f;
    else if (keyStates[LEFT])
        direction_vector.x = -1.f;
    else if (keyStates[RIGHT])
        direction_vector.x = 1.f;
    if ((keyStates[UP] && keyStates[DOWN]) || (!keyStates[UP] && !keyStates[DOWN]))
        direction_vector.y = 0.f;
    else if (keyStates[UP])
        direction_vector.y = -1.f;
    else if (keyStates[DOWN])
        direction_vector.y = 1.f;

}
