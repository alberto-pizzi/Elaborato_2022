//
// Created by alber on 01/12/2022.
//

#ifndef ELABORATO_GAMECHARACTERFIXTURE_H
#define ELABORATO_GAMECHARACTERFIXTURE_H

#include "gtest/gtest.h"
#include "../Mike.h"
#include "../ArenaMap.h"
#include "../Spawner.h"
#include "../PlayState.h"
#include "../Game.h"
#include <memory>


class GameCharacterFixture : public ::testing::Test {
protected:
    sf::Texture mikeTex;
    sf::Texture weaponTex;
    sf::Texture bulletTex;
    sf::Context context;
    std::unique_ptr<Mike> mike;
    //std::unique_ptr<Spawner> spawner;
    sf::Vector2i spawnTile = {40, 24};
    TextureManager fakeTexManager;
public:
    GameCharacterFixture();

    virtual ~GameCharacterFixture();
};


#endif //ELABORATO_GAMECHARACTERFIXTURE_H
