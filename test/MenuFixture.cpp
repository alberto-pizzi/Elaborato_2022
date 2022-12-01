//
// Created by alber on 01/12/2022.
//

#include "MenuFixture.h"


MenuFixture::~MenuFixture() {
    delete play;
}

MenuFixture::MenuFixture() {
    play = new PlayState(&game);
}
