//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_POSENTITY_H
#define ELABORATO_POSENTITY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


class PosEntity {
protected:
    sf::FloatRect pos;
    sf::Vector2f spriteCenter;
public:
    PosEntity();

    void updateGlobalPosition(sf::FloatRect newGlobalPos);

    virtual void move(const sf::Vector2f &offset, float dt) = 0;

    virtual ~PosEntity() = default;

    const sf::FloatRect &getPos() const;

    const sf::Vector2f &getSpriteCenter() const;
};


#endif //ELABORATO_POSENTITY_H
