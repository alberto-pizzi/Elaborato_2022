//
// Created by alber on 21/12/2022.
//

#include "ArenaMapFixture.h"

ArenaMapFixture::~ArenaMapFixture() {
    delete map;
}

ArenaMapFixture::ArenaMapFixture() {
    if ((!mikeTex.loadFromFile("../res/textures/no_hands_mike.png")) &&
        (!weaponTex.loadFromFile("../res/textures/handgun.png")) &&
        (!bulletTex.loadFromFile("../res/textures/bullet.png")))
        std::cerr << "Error opening mike texture" << std::endl;
    else {

        map = new ArenaMap(0, fakeWindow, mike, mikeTex, weaponTex, bulletTex, textureManager, 10, {40 * 32, 23 * 32});
    }
}
