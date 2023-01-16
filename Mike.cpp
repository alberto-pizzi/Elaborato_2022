//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
           const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, float startRoundCountdownSeconds, bool animated, int hp, float speed,
           unsigned int points, unsigned int coins, int armor, bool bubble, int streak)
        : GameCharacter(mikeTexture, hp,
                        speed,
                        points,
                        spawnTile,
                        tileSize,
                        rectSkin, MIKE, {0, 0}, 5,
                        animated,
                        coins,
                        armor,
                        bubble),
          killStreak(streak), gui(this->points, 1, 12, 12, true, startRoundCountdownSeconds, handgunTexture,
                                  guiTexManager) { //WARNING: Mike's damage hit never will be used

    weapon = std::unique_ptr<Weapon>(new Handgun(true, handgunTexture, handgunBulletTexture));
    gui.updateWeaponType(handgunTexture, weapon->currentAnimation.idleFrames[0], weapon->hitBox.getSize());
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

Mike::~Mike() = default;

