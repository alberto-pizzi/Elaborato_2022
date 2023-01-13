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

const int nEnemyTypes = 3; //FIXME

class GameCharacter : public PosEntity {
private:
    int characterType;
    sf::Time hitTimeColor = sf::seconds(0.3);

    bool isHit = false;
    const sf::Color bubbleColor = sf::Color(0, 191, 255);
    const sf::Color hitColor = sf::Color(102, 0, 0);
protected:
    float HP;
    int armor; //float
    float speed;
    sf::Vector2f damageHit; //damage is included between min and max values x = MIN y = MAX
    bool bubble;
    unsigned int points;
    unsigned int coins;
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::IntRect> goRight;
    std::vector<sf::IntRect> goLeft;
    std::vector<sf::IntRect> goDown;
    std::vector<sf::IntRect> goUp;
    std::vector<sf::IntRect> idle;
    std::vector<sf::IntRect> death;
    const int deathFrames = 8;
    sf::Vector2i fileTextureRectSkinSize;

    //hit attributes
    float hitRange; //in coords
    sf::Clock hitClock;
    sf::Time nextHitTime = sf::seconds(1);
    Dice randomDice;

    //the protected constructor is to make the class non-instantiable (like an abstract class)
    GameCharacter(const sf::Texture &tex, float hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
                  const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, sf::Vector2f damageHit,
                  float hitRange = 5, bool animated = true, unsigned int coins = 0, int armor = 0, bool bubble = false);

public:
    bool keyStates[4] = {false, false, false, false};
    sf::Vector2f direction_vector = sf::Vector2f(0.f, 0.f);

    //enemy AI
    bool attachedToNodes = false;
    sf::Vector2f target;
    bool achieved;

    //death animation
    bool despawnStarted = false;
    bool isDeathAnimationActive = false;
    bool isDeathAnimationEnded = false;


    sf::Clock hitColorClock; //FIXME getter

    bool skinDirection[4] = {false, false, false, false};
    std::unique_ptr<Weapon> weapon;
    Animation currentAnimation{idle, 10.0f};

    const sf::Sprite &getSprite() const;


    virtual ~GameCharacter();

    void move(const sf::Vector2f &offset, float dt) override;

    void characterSkinDirection(const sf::Vector2f &targetPos);

    sf::FloatRect futureCharacterPosition(const sf::Vector2f &offset, float dt);

    virtual void receiveDamage(float damagePoints);

    void updateCharacterColor();

    bool isDead() const;

    void startDespawning();

    virtual void hit(GameCharacter &target);

    float damageWithArmor(float damagePoints) const;

    virtual bool isAbleToHit(const GameCharacter &target);

    sf::Vector2f normalize(sf::Vector2f vector) const;

    bool isLegalFight(const GameCharacter &enemy) const;

    virtual void drawEntity(sf::RenderWindow &window, bool gameOver);

    float getHp() const;

    int getArmor() const;

    bool isBubble() const;

    int getPoints() const;

    int getCoins() const;

    int getSpeed() const;

    void setHp(float hp);

    void setArmor(int armor);

    void setSpeed(float speed);

    void setBubble(bool bubble);

    void setPoints(int points);

    void setCoins(int coins);

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

    void calculateDirectionVector();

    void calculateEnemyMoveDirectionArray(sf::Vector2f offset);

    const sf::Color &getHitColor() const;
};


#endif //ELABORATO_GAMECHARACTER_H
