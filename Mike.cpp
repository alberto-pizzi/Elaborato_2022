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
                        rectSkin, MIKE,
                        animated,
                        coins,
                        armor,
                        bubble),
          killStreak(streak), gui(this->points, 1, 12, 12, true, handgunTexture, guiTexManager) {
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

void Mike::move(const sf::Vector2f &offset, float dt) {
    float newSpeed = this->speed;
    sf::Vector2f effectiveOffset;

    //set diagonal speed
    if (((offset.y > 0) && (offset.x > 0)) || ((offset.y > 0) && (offset.x < 0)) ||
            ((offset.y < 0) && (offset.x > 0)) || ((offset.y < 0) && (offset.x < 0)))
        newSpeed /= std::sqrt(2.f);

    effectiveOffset = offset * newSpeed * dt;
    sprite.setPosition(sprite.getPosition() + effectiveOffset);
    //pos = sprite.getGlobalBounds();
    updateGlobalPosition(sprite.getGlobalBounds());
}

void Mike::directionInput(const sf::Vector2f &viewfinderPos, bool (&skinDirection)[4]) {
    //set Cartesian plane as player position
    sf::Vector2f origin = spriteCenter;
    sf::Vector2f translation = viewfinderPos - origin;
    float frameDuration = 0.5f;
    float radians, degrees;


    //weapon angle from input
    radians = std::atan(translation.y / translation.x);
    degrees = radians * static_cast<float>(180 / M_PI);

    //when mouse exceeds bisects (+- 45°) of all quadrants, Mike changes body direction
    if (viewfinderPos.x >= origin.x) {
        weapon->weaponSprite.setScale(sf::Vector2f(1, 1));
        if ((translation.y < translation.x) && (translation.y > -(translation.x))) {
            currentAnimation.setMovementAnimation(goRight, frameDuration, RIGHT);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = true;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        } else if (viewfinderPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = true;
        } else if (viewfinderPos.y < origin.y) {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            skinDirection[UP] = true;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        }
    } else if (viewfinderPos.x < origin.x) {
        weapon->weaponSprite.setScale(sf::Vector2f(-1, 1));
        if ((translation.y > translation.x) && (translation.y < -(translation.x))) {
            currentAnimation.setMovementAnimation(goLeft, frameDuration, LEFT);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = true;
            skinDirection[DOWN] = false;
        } else if (viewfinderPos.y >= origin.y) {
            currentAnimation.setMovementAnimation(goDown, frameDuration, DOWN);
            skinDirection[UP] = false;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = true;
        } else {
            currentAnimation.setMovementAnimation(goUp, frameDuration, UP);
            skinDirection[UP] = true;
            skinDirection[RIGHT] = false;
            skinDirection[LEFT] = false;
            skinDirection[DOWN] = false;
        }
    }

    if (weapon->getWeaponName() == "handgun")
        weapon->weaponSprite.setOrigin(sf::Vector2f(0, 0));
    else if (weapon->getWeaponName() == "assaultRifle")
        weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));
    else if (weapon->getWeaponName() == "shotgun")
        weapon->weaponSprite.setOrigin(sf::Vector2f(21, 10));

    weapon->weaponSprite.setRotation(degrees);
    weapon->setDegrees(degrees);

    //hit box
    weapon->hitBox.setScale(weapon->weaponSprite.getScale());
    weapon->hitBox.setRotation(degrees);
}

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

Mike::~Mike() = default;

