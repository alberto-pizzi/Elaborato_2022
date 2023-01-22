//
// Created by alber on 12/11/2022.
//

#include "Mike.h"
#include "Bonus.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
           const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, float hp, float speed, int armor)
        : GameCharacter(mikeTexture, hp,
                        speed,
                        0,
                        spawnTile,
                        tileSize,
                        rectSkin, MIKE, {0, 0}, 5,
                        true,
                        0,
                        armor,
                        false),
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

    AchievementManager::createInstance(this, guiTexManager);

    AchievementManager::getInstance()->createAchievement("Kill 5 enemies", "Kill 5 enemies with a weapon", 5);

    AchievementManager::getInstance()->createAchievement("Kill 10 enemies", "Kill 10 enemies with a weapon", 10);
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

void Mike::drawEntity(sf::RenderWindow &window, bool gameOver) {
    if (!skinDirection[UP]) {
        GameCharacter::drawEntity(window, gameOver);
        if (!gameOver)
            weapon->drawWeapon(window);
    } else {
        if (!gameOver)
            weapon->drawWeapon(window);
        GameCharacter::drawEntity(window, gameOver);
    }
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

void Mike::notifyObserver(std::string achievementName, unsigned int value) const {
    for (auto itr = std::begin(observers); itr != std::end(observers); itr++)
        (*itr)->update(achievementName, value);
}

void Mike::incrementKills(int enemyType) {
    enemyTypeKills[enemyType]++;
    roundKills++;
    kills++;
    notifyObserver("Kill 5 enemies", this->kills); //FIXME

    notifyObserver("Kill 10 enemies", this->kills); //FIXME
}

void Mike::resetRoundKills() {
    roundKills = 0;
}

