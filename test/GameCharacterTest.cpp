//
// Created by alber on 27/11/2022.
//
#include "gtest/gtest.h"

#include "../GameCharacter.h"
#include "../Mike.h"


TEST (Mike, CorrectSpriteCenter) {
    sf::Context context;
    Mike mike(0, 0);
    //only with 32x32 player sprite
    EXPECT_EQ(16, mike.getPos().x);
    EXPECT_EQ(16, mike.getPos().y);
}



