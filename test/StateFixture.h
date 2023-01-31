//
// Created by alber on 01/12/2022.
//

#ifndef ELABORATO_STATEFIXTURE_H
#define ELABORATO_STATEFIXTURE_H

#include "gtest/gtest.h"
#include "../PlayState.h"
#include "../Game.h"


class StateFixture : public ::testing::Test {
protected:
    Game game;
    PlayState *play;
    sf::Context context;
public:
    StateFixture();

    virtual ~StateFixture();
};


#endif //ELABORATO_STATEFIXTURE_H
