//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "GameState.h"
#include "ArenaMap.h"
#include "Spawner.h"
#include "Mike.h"
#include "TextureManager.h"

//WARNING: for adding other Map, you must update nMap/loadMap and enum in ArenaMap.h
const int nMap = 1;



class PlayState : public GameState {
private:

    sf::View gameView;
    sf::View guiView;
    ArenaMap *arenaMap;
private:
    //TODO add pause menu method - MenuState.cpp (load game)
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<Mike> mike;
    bool keyStates[4] = {false, false, false, false};
    sf::Vector2f direction_vector = sf::Vector2f(0.f, 0.f);
    sf::Clock frame_clock;

    sf::Sprite viewfinderSprite;
    TextureManager textureManager;

public:
    explicit PlayState(Game *game);

    ArenaMap *getArenaMap() const;

    void draw(float dt) override;

    void update(float dt) override;

    void handleInput() override;

    int whichMap();

    sf::Vector2f normalize(sf::Vector2f vector);
};

#endif //ELABORATO_PLAYSTATE_H
