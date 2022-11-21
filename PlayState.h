//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

#include "GameState.h"
#include "ArenaMap.h"
#include "Spawner.h"
#include "Mike.h"

//WARNING: for adding other Map, you must update nMap/loadMap and enum in ArenaMap.h
const int nMap = 1;

enum Directions {
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3,
};

class PlayState : public GameState {
private:

    sf::View gameView;
    sf::View guiView;
    ArenaMap *arenaMap;
    //TODO add pause menu method - MenuState.cpp (load game)
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<Mike> mike;
    bool key_states[4] = {false, false, false, false};
    float mikeSpeed = 250.f;
    sf::Vector2f direction_vector = sf::Vector2f(0.f, 0.f);
    sf::Clock frame_clock;
public:
    explicit PlayState(Game *game);

    void draw(float dt) override;

    void update(float dt) override;

    void handleInput() override;

    void whichMap();

    sf::Vector2f normalize(sf::Vector2f vector);
};

#endif //ELABORATO_PLAYSTATE_H
