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

class GameCharacter : public PosEntity {
protected:
    int HP;
    int armor;
    int speed;
    bool bubble;
    int points;
    int coins;
    sf::RectangleShape character; //TODO remove it (for debug)
public:
    GameCharacter(int hp, int speed, int points, int coins = 0, int armor = 0, bool bubble = false);

    void move(sf::Vector2f pos) override = 0;

    int receiveDamage(int damagePoints, bool armor);

    void chase(GameCharacter &enemy);

    bool isLegalFight(const GameCharacter &enemy) const;

    virtual void drawEntity(sf::RenderWindow &window) = 0;

};


#endif //ELABORATO_GAMECHARACTER_H
