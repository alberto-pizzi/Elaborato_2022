//
// Created by alber on 03/11/2022.
//

#ifndef ELABORATO_POSENTITY_H
#define ELABORATO_POSENTITY_H


class PosEntity {
protected:
    sf::Vector2f pos;
public:
    void setPos(const sf::Vector2f &p) {
        this->pos = p;
    }

    const sf::Vector2f &getPos() const {
        return pos;
    }

    virtual void move(const sf::Vector2f &offset, float dt) = 0;

    virtual void drawEntity(sf::RenderWindow &window) = 0;
};


#endif //ELABORATO_POSENTITY_H
