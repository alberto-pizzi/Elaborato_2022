//
// Created by alber on 24/10/2022.
//

#ifndef ELABORATO_GAMESTATE_H
#define ELABORATO_GAMESTATE_H

#include "Game.h"

class GameState {
protected:
    const sf::Vector2f viewSize = {40 * 32, 23 * 32};
public:
    GameState();

    virtual ~GameState();

    Game *game;

    virtual void draw(float dt) const = 0;

    virtual void update(float dt) = 0;

    virtual void handleInput() = 0;
};


#endif //ELABORATO_GAMESTATE_H
