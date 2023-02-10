//
// Created by alber on 10/02/2023.
//

#ifndef ELABORATO_ACHIEVEMENTFIXTURE_H
#define ELABORATO_ACHIEVEMENTFIXTURE_H

#include "gtest/gtest.h"
#include "../Mike.h"

class AchievementFixture : public ::testing::Test {
protected:
    sf::Texture mikeTex;
    sf::Texture weaponTex;
    sf::Texture bulletTex;
    sf::Context context;
    sf::Vector2i spawnTile = {40, 24};
    TextureManager textureManager;
};


#endif //ELABORATO_ACHIEVEMENTFIXTURE_H
