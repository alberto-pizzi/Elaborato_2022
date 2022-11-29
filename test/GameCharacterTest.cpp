#include "gtest/gtest.h"

#include "../GameCharacter.h"
#include "../Mike.h"
#include "../Gui.h"

//FIXME fix all unit testing (fixture)

TEST (Mike, CorrectSpriteCenter) {
    sf::Context context;
    sf::Texture tex;
    Mike mike(tex, 0, 0);
    //only with 32x32 player healthBar. Replace "32/2=16" with different dimensions.
    EXPECT_EQ(16, mike.getPos().x);
    EXPECT_EQ(16, mike.getPos().y);
}

TEST (HealthBar, TotalHPTest) {
    sf::Context context;
    sf::Texture tex;
    Mike mike(tex, 0, 0);
    Gui gui;

    //HP must be equal to Up
    EXPECT_EQ(20, mike.getHp());
    EXPECT_EQ(5 * 32, gui.getTexManager().getTextureRef("healthBar").getSize().x);
}
