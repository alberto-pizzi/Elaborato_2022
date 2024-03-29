//
// Created by alber on 23/10/2022.
//
#include <SFML/System.hpp>

#include "Game.h"
#include "GameState.h"

void Game::pushState(GameState *state) {
    this->states.push(state);
}

void Game::popState() {
    //delete this->states.top();
    this->states.pop();
}

void Game::changeState(GameState *state) {
    if (!this->states.empty())
        popState();
    pushState(state);
}

GameState *Game::lookState() {
    if (this->states.empty())
        return nullptr;
    return this->states.top();
}

void Game::gameLoop() {
    sf::Clock clock;
    float dt;

    while (this->window.isOpen()) {
        dt = clock.restart().asSeconds();

        if (lookState() != nullptr) {
            lookState()->handleInput();
            lookState()->update(dt);
            this->window.clear(sf::Color::Black);
            lookState()->draw(dt);
            this->window.display();
        }
    }
}

Game::Game() {
    sf::Context context; //it is used to fix an error on OpenGL()

    this->loadTextures();
    this->window.create(sf::VideoMode(1280, 736), "Game_window", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);
    this->background.setTexture(this->textureManager.getTextureRef("background"));
}

Game::~Game() {
    while (!this->states.empty())
        popState();
}

void Game::loadTextures() {
    textureManager.loadTexture("background", "res/textures/main_menu_background.jpg");
    textureManager.loadTexture("button", "res/textures/menu_button.png");
    textureManager.loadTexture("mike", "res/textures/mike.png");
}
