#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Game.h"
#include "MenuState.h"

int main() {
    Game game;
    game.pushState(new MenuState(&game));
    game.gameLoop();

    return 0;
}