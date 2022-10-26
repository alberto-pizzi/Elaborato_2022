//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include "GameState.h"

class PlayState : public GameState {
private:

    sf::View gameView;
    sf::View guiView;
    //TODO add pause menu method - MenuState.cpp (load game)

public:
    explicit PlayState(Game *game);

    virtual void draw(float dt);

    virtual void update(float dt);

    virtual void handleInput();
};

#endif //ELABORATO_PLAYSTATE_H
