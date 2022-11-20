//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include <cstdlib>
#include <ctime>

#include "GameState.h"
#include "ArenaMap.h"
#include "Spawner.h"
#include "Mike.h"

//WARNING: for adding other Map, you must update nMap/loadMap and enum in ArenaMap.h
const int nMap = 1;

class PlayState : public GameState {
private:

    sf::View gameView;
    sf::View guiView;
    ArenaMap *arenaMap;
    //TODO add pause menu method - MenuState.cpp (load game)
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<Mike> mike;

public:
    explicit PlayState(Game *game);

    void draw(float dt) override;

    void update(float dt) override;

    void handleInput() override;

    void whichMap();
};

#endif //ELABORATO_PLAYSTATE_H
