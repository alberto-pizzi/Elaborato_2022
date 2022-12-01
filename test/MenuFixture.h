//
// Created by alber on 01/12/2022.
//

#ifndef ELABORATO_MENUFIXTURE_H
#define ELABORATO_MENUFIXTURE_H

#include "gtest/gtest.h"
#include "../PlayState.h"
#include "../Game.h"


class MenuFixture : public ::testing::Test {
protected:
    Game game;
    PlayState *play;
    sf::Context context;
public:
    MenuFixture();

    virtual ~MenuFixture();
};


#endif //ELABORATO_MENUFIXTURE_H
