//
// Created by alber on 01/12/2022.
//

#include "GameCharacterFixture.h"

GameCharacterFixture::~GameCharacterFixture() = default;

GameCharacterFixture::GameCharacterFixture() {
    if ((!mikeTex.loadFromFile("../res/textures/no_hands_mike.png")) &&
        (!weaponTex.loadFromFile("../res/textures/handgun.png")))
        std::cerr << "Error opening mike texture" << std::endl;
    else {
        mike = std::unique_ptr<Mike>(new Mike(mikeTex, weaponTex, {40, 24}, {32, 32}, {32, 32}, true, 20, 250));
    }

}
