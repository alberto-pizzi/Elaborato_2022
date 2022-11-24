//
// Created by alber on 18/10/2022.
//

#ifndef ELABORATO_GAMECHARACTER_H
#define ELABORATO_GAMECHARACTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "PosEntity.h"
#include "Animation.h"

class GameCharacter : public PosEntity {
protected:
    int HP;
    int armor;
    int speed;
    bool bubble;
    int points;
    int coins;
    sf::RectangleShape character; //TODO remove it (for debug)

    std::vector<sf::IntRect> goRight;
    std::vector<sf::IntRect> goLeft;
    std::vector<sf::IntRect> goDown;
    std::vector<sf::IntRect> goUp;
    std::vector<sf::IntRect> idle;


public:
    const sf::RectangleShape &getCharacter() const;

    GameCharacter(int hp, int speed, int points, int coins = 0, int armor = 0, bool bubble = false);

    void move(const sf::Vector2f &offset, float dt) override = 0;

    int receiveDamage(int damagePoints, bool armor);

    void chase(GameCharacter &enemy);

    bool isLegalFight(const GameCharacter &enemy) const;

    virtual void drawEntity(sf::RenderWindow &window) = 0;


};


#endif //ELABORATO_GAMECHARACTER_H
