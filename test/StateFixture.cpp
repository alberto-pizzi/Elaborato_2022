//
// Created by alber on 01/12/2022.
//

#include "StateFixture.h"


StateFixture::~StateFixture() {
    delete play;
}

StateFixture::StateFixture() {
    play = new PlayState(&game);
}
