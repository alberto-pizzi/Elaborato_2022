//
// Created by alber on 01/12/2022.
//

#include "GameCharacterFixture.h"

GameCharacterFixture::~GameCharacterFixture() = default;

GameCharacterFixture::GameCharacterFixture() {
    if ((!mikeTex.loadFromFile("../res/textures/no_hands_mike.png")) &&
        (!weaponTex.loadFromFile("../res/textures/handgun.png")) &&
        (!bulletTex.loadFromFile("../res/textures/bullet.png")))
        std::cerr << "Error opening mike texture" << std::endl;
    else {
        textureManager.loadTexture("healthBar", "res/textures/progressbar.png");
        mike = std::unique_ptr<Mike>(new Mike(mikeTex, weaponTex, bulletTex, spawnTile, textureManager, {32, 32},
                                              {32, 32}, 5,
                                              20, 250));
    }
}
