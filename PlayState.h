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
#include "Gui.h"

//WARNING: for adding other Map, you must updateNotCyclicalAnimation nMap/loadMap and enum in ArenaMap.h
const int nMap = 1;



class PlayState : public GameState {
private:
    sf::View gameView;
    sf::View guiView;
    ArenaMap *arenaMap;
    //TODO add pause menu method - MenuState.cpp (loadTextures game)
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<Mike> mike;
    bool keyStates[4] = {false, false, false, false};
    sf::Vector2f direction_vector = sf::Vector2f(0.f, 0.f);
    sf::Clock frame_clock;
    int round;
    bool isUp = false;

    //animation settings
    bool isEnded = false;
    bool isActiveAnimation = false;

    sf::Sprite viewfinderSprite;
    TextureManager textureManager;
public:
    explicit PlayState(Game *game);

    virtual ~PlayState();

    ArenaMap *getArenaMap() const;

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;

    int whichMap();

    sf::Vector2f normalize(sf::Vector2f vector);

    void loadTextures();
};

#endif //ELABORATO_PLAYSTATE_H
