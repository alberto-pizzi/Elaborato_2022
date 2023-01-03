//
// Created by alber on 12/11/2022.
//

#include "Mike.h"


bool Mike::isKillStreak(GameCharacter &character) {
    return false;
}

Mike::Mike(const sf::Texture &mikeTexture, const sf::Texture &handgunTexture, const sf::Texture &handgunBulletTexture,
           const sf::Vector2i &spawnTile, const TextureManager &guiTexManager, const sf::Vector2i &tileSize,
           const sf::Vector2i &rectSkin, bool animated, int hp, float speed, unsigned int points, unsigned int coins,
           int armor, bool bubble, int streak)
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
          killStreak(streak), gui(this->points, 1, 12, 12, true, handgunTexture,
                                  guiTexManager) { //WARNING: Mike's damage hit never will be used
    this->sprite.setScale(sf::Vector2f(1.5, 1.5));
    //WARNING: work here to edit frames
    goDown.reserve(3);
    goDown = {
            {0 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 0 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goLeft.reserve(3);
    goLeft = {
            {0 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 1 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goRight.reserve(3);
    goRight = {
            {0 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 2 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    goUp.reserve(3);
    goUp = {
            {0 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {1 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
            {2 * this->fileTextureRectSkinSize.x, 3 *
                                                  this->fileTextureRectSkinSize.y, this->fileTextureRectSkinSize.x, this->fileTextureRectSkinSize.y},
    };

    weapon = std::unique_ptr<Weapon>(new Handgun(true, handgunTexture, handgunBulletTexture));
    gui.updateWeaponType(handgunTexture, weapon->currentAnimation.idleFrames[0], weapon->hitBox.getSize());
}

/*
void Mike::drawEntity(sf::RenderWindow &window) {
    sprite.setTextureRect(currentAnimation.getCurrentRect());
    window.draw(sprite);
}
*/



void Mike::setWeaponPosToShouldersPos() {
    if (currentAnimation.frames == goRight)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[RIGHT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[RIGHT].y);
    else if (currentAnimation.frames == goLeft)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width +
                                         weapon->startCenterForTranslation[LEFT].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[LEFT].y);
    else if (currentAnimation.frames == goUp)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[UP].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[UP].y);
    else if (currentAnimation.frames == goDown)
        weapon->weaponSprite.setPosition(this->sprite.getPosition().x + weapon->startCenterForTranslation[DOWN].x,
                                         this->sprite.getPosition().y + weapon->startCenterForTranslation[DOWN].y);

    weapon->hitBox.setPosition(weapon->weaponSprite.getPosition());
}

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

void Mike::drawEntity(sf::RenderWindow &window) {
    if (!skinDirection[UP]) {
        GameCharacter::drawEntity(window);
        weapon->drawWeapon(window);
    } else {
        weapon->drawWeapon(window);
        GameCharacter::drawEntity(window);
    }
}

Mike::~Mike() = default;

