//
// Created by alber on 23/10/2022.
//

#ifndef ELABORATO_GAME_H
#define ELABORATO_GAME_H

#include <stack>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "TextureManager.h"

class GameState;

class Game {
private:
    void loadTextures();

public:
    Game();

    ~Game();

    std::stack<GameState *> states;
    sf::RenderWindow window;
    TextureManager texmgr;
    sf::Sprite background;

    void pushState(GameState *state);

    void popState();

    void changeState(GameState *state);

    GameState *lookState();

    void gameLoop();
};


#endif //ELABORATO_GAME_H
