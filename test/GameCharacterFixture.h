//
// Created by alber on 01/12/2022.
//

#ifndef ELABORATO_GAMECHARACTERFIXTURE_H
#define ELABORATO_GAMECHARACTERFIXTURE_H

#include "gtest/gtest.h"
#include "../Mike.h"
#include "../ArenaMap.h"
#include <memory>


class GameCharacterFixture : public ::testing::Test {
protected:
    sf::Texture mikeTex;
    sf::Texture weaponTex;
    sf::Texture bulletTex;
    sf::Context context;
    std::unique_ptr<Mike> mike;
public:
    GameCharacterFixture();

    virtual ~GameCharacterFixture();
};


#endif //ELABORATO_GAMECHARACTERFIXTURE_H
