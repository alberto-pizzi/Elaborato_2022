//
// Created by alber on 18/10/2022.
//

#ifndef ELABORATO_GAMECHARACTER_H
#define ELABORATO_GAMECHARACTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

#include "PosEntity.h"
#include "Animation.h"
#include "TextureManager.h"
#include "Weapon.h"
#include "Handgun.h"
#include "AssaultRifle.h"
#include "Shotgun.h"
#include "GameException.h"
#include "Dice.h"

enum Directions {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};

enum GameCharacterType {
    MIKE = 0, ZOMBIE, ARCHER, BOSS, WARRIOR, KAMIKAZE
};

enum GameCharacterSize {
    spriteSizeX = 32, spriteSizeY = 32,
};

const int totalDirections = 4;

class GameCharacter : public PosEntity {
private:
    int characterType;
    float defaultHP;
protected:
    float HP;
    float armor;
    float speed;
    sf::Vector2f damageHit; //damage is included between min and max values x = MIN y = MAX
    bool isHit = false;
    unsigned int points;
    unsigned int coins;
    sf::Texture texture;
    sf::Sprite sprite;

    //animation
    std::vector<sf::IntRect> goRight;
    std::vector<sf::IntRect> goLeft;
    std::vector<sf::IntRect> goDown;
    std::vector<sf::IntRect> goUp;
    std::vector<sf::IntRect> idle;
    std::vector<sf::IntRect> death;
    const int deathFrames = 8;
    const int directionMovementAnimationFrames = 3;
    sf::Vector2i fileTextureRectSkinSize;

    //colors
    const sf::Color bubbleColor = sf::Color(0, 191, 255);
    const sf::Color hitColor = sf::Color(102, 0, 0);

    //hit attributes

    sf::Clock hitClock;
    sf::Time nextHitTime = sf::seconds(1);
    Dice randomDice;
    const sf::Time hitTime = sf::seconds(0.3);

    //audio
    AudioManager audioManager;
public:
    sf::Clock hitColorClock;

    GameCharacter(const sf::Texture &tex, float hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
                  const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
                  bool animated = true, unsigned int coins = 0, float armor = 0);

    bool skinDirection[totalDirections] = {false, false, false, false};

    //death animation
    bool despawnStarted = false;
    bool isDeathAnimationActive = false;
    bool isDeathAnimationEnded = false;

    //weapon
    std::unique_ptr<Weapon> weapon;

    //animation
    Animation currentAnimation{idle, 10.0f};

    const sf::Sprite &getSprite() const;


    virtual ~GameCharacter();

    void move(const sf::Vector2f &offset, float dt) override;

    void characterSkinDirection(const sf::Vector2f &targetPos);

    sf::FloatRect futureCharacterPosition(const sf::Vector2f &offset, float dt);

    virtual void receiveDamage(float damagePoints) = 0;

    virtual void updateCharacterColor() = 0;

    bool isDead() const;

    void startDespawning();

    void setWeaponPosToShouldersPos();

    float damageWithArmor(float damagePoints) const;

    sf::Vector2f normalize(sf::Vector2f vector) const;

    virtual void drawEntity(sf::RenderWindow &window);

    float getHp() const;

    int getArmor() const;

    int getPoints() const;

    int getCoins() const;

    int getSpeed() const;

    void setHp(float hp);

    void setArmor(int armor);

    void setSpeed(float speed);

    virtual void setPoints(int points);

    virtual void setCoins(int coins);

    const std::vector<sf::IntRect> &getGoRight() const;

    const std::vector<sf::IntRect> &getGoLeft() const;

    const std::vector<sf::IntRect> &getGoDown() const;

    const std::vector<sf::IntRect> &getGoUp() const;

    const std::vector<sf::IntRect> &getDeath() const;

    void setSpritePos(sf::Vector2f newPos);

    bool isHit1() const;

    void setIsHit(bool isHit);

    int getCharacterType() const;

    const sf::Vector2f &getDamageHit() const;

    const sf::Color &getHitColor() const;

    float getDefaultHp() const;

    float calculateDistanceBetweenPositions(sf::Vector2f pos1, sf::Vector2f pos2) const;

    void loadSounds();
};


#endif //ELABORATO_GAMECHARACTER_H
