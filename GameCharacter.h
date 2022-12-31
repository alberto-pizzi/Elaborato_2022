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

enum Directions {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};

enum GameCharacterType {
    MIKE = 0, ZOMBIE, ARCHER, BOSS, WARRIOR, KAMIKAZE
};

class GameCharacter : public PosEntity {
private:
    int characterType;
    sf::Time hitTimeColor = sf::seconds(0.3);

    bool isHit = false;
    const sf::Color bubbleColor = sf::Color(0, 191, 255);
    const sf::Color hitColor = sf::Color(102, 0, 0);
protected:
    float HP;
    int armor;
    float speed;
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
    sf::Vector2i fileTextureRectSkinSize;

    //hit attributes
    float hitRange; //in coords
    float oldHP = HP;
    sf::Clock hitClock;
    sf::Time nextHitTime = sf::seconds(1);

public:
    sf::Clock hitColorClock;

    bool skinDirection[4] = {false, false, false, false};
    std::unique_ptr<Weapon> weapon;
    Animation currentAnimation{idle, 10.0f};

    const sf::Sprite &getSprite() const;

    GameCharacter(const sf::Texture &tex, int hp, float speed, unsigned int points, const sf::Vector2i &tilePosition,
                  const sf::Vector2i &tileSize, const sf::Vector2i &rectSkin, int characterType, float hitRange = 5,
                  bool animated = true, unsigned int coins = 0, int armor = 0, bool bubble = false);

    virtual ~GameCharacter();

    void move(const sf::Vector2f &offset, float dt) override = 0;

    void characterSkinDirection(const sf::Vector2f &targetPos);

    void receiveDamage(int damagePoints);

    void updateCharacterColor();

    int howMuchDamage() const;

    bool isAbleToHit(const GameCharacter &target);

    sf::Vector2f normalize(sf::Vector2f vector);

    bool isLegalFight(const GameCharacter &enemy) const;

    void drawEntity(sf::RenderWindow &window);

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

    void setSpritePos(sf::Vector2f newPos);

    bool isHit1() const;

    void setIsHit(bool isHit);
};


#endif //ELABORATO_GAMECHARACTER_H
