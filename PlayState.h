//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include <cstdlib>
#include <ctime>

#include "GameState.h"
#include "ArenaMap.h"

class PlayState : public GameState {
private:

    sf::View gameView;
    sf::View guiView;
    //std::unique_ptr<ArenaMap> arenaMap;

    ArenaMap *arenaMap;
    //TODO add pause menu method - MenuState.cpp (load game)

public:
    explicit PlayState(Game *game);

    virtual void draw(float dt);

    virtual void update(float dt);

    virtual void handleInput();

    void whichMap();
};

#endif //ELABORATO_PLAYSTATE_H
