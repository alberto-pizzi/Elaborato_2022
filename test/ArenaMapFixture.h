//
// Created by alber on 21/12/2022.
//

#ifndef ELABORATO_ARENAMAPFIXTURE_H
#define ELABORATO_ARENAMAPFIXTURE_H

#include "gtest/gtest.h"
#include "../Mike.h"
#include "../ArenaMap.h"
#include <memory>

class ArenaMapFixture : public ::testing::Test {
protected:
    sf::Texture mikeTex;
    sf::Texture weaponTex;
    sf::Texture bulletTex;
    ArenaMap *map;
    sf::Context context;
    std::unique_ptr<Mike> mike;
    sf::RenderWindow fakeWindow;
    TextureManager textureManager;
public:
    ArenaMapFixture();

    virtual ~ArenaMapFixture();
};


#endif //ELABORATO_ARENAMAPFIXTURE_H
