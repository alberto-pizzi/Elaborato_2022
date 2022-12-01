//
// Created by alber on 01/12/2022.
//

#include "GameCharacterFixture.h"

GameCharacterFixture::~GameCharacterFixture() = default;

GameCharacterFixture::GameCharacterFixture() {
    if (!tex.loadFromFile("../res/textures/mike.png"))
        std::cerr << "Error opening mike texture" << std::endl;
    else {
        mike = std::unique_ptr<Mike>(new Mike(tex, {40, 24}, {32, 32}, {32, 32}, true, 20, 250));
    }

}
