//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_POSENTITY_H
#define ELABORATO_POSENTITY_H


class PosEntity {
protected:
    sf::Vector2f pos;
public:
    const sf::Vector2f &getPos() const {
        return pos;
    }

    virtual void move(sf::Vector2f pos) = 0;

    virtual void drawEntity(sf::RenderWindow &window) = 0;
};


#endif //ELABORATO_POSENTITY_H
